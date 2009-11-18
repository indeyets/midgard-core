/* 
 * Copyright (C) 2009 Piotr Pokora <piotrek.pokora@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <glib.h>
#include <glib-object.h>
#include "midgard_defs.h"
#include "midgard_storage.h"
#include "midgard_core_object.h"
#include "midgard_core_query.h"
#include "midgard_user.h"
#include "midgard_core_connection.h"

#define ADMIN_USER_GUID "f4edf43cc32a11deb15c11e64583ae10ae10"
#define ADMIN_PERSON_GUID "f6b665f1984503790ed91f39b11b5392"
#define ADMIN_USER_LOGIN "admin"
#define ADMIN_USER_PASSWORD "password"

#define DEFAULT_AUTH_TYPE "Plaintext"

struct _MidgardStorage {
	GObject parent;
};

struct _MidgardStorageClass {
	GObjectClass parent;
};

/**
 * midgard_storage_create_base_storage:
 * @mgd: #MidgardConnection instance 
 *
 * Creates storage for base Midgard classes.
 * Tables created by this method: repligard, midgard_user and midgard_person.
 * 
 * Returns: %TRUE if tables has been created, %FALSE otherwise.
 *
 * Since: 9.09
 */
gboolean
midgard_storage_create_base_storage(MidgardConnection *mgd)
{
	g_return_val_if_fail(mgd != NULL, FALSE);

	gboolean ret =  midgard_core_query_create_basic_db(mgd);

	if(!ret)
		return FALSE;
	
	/* Create midgard_user storage */
	MidgardUserClass *user_klass = MIDGARD_USER_CLASS(G_OBJECT_CLASS (g_type_class_peek (MIDGARD_TYPE_USER)));
	midgard_storage_create_class_storage (mgd, MIDGARD_DBOBJECT_CLASS (user_klass));

	GString *query = g_string_new ("SELECT id from midgard_user where guid = ");
	g_string_append_printf (query, "'%s'", ADMIN_USER_GUID);
	const gchar *sql = query->str;

	GdaDataModel *model = midgard_core_query_get_model(mgd, sql);
	guint ret_rows = 0;

	if(model)
		ret_rows = gda_data_model_get_n_rows(model);

        if(!model || ret_rows == 0) {

		/* Enable admin login */
		GString *query = g_string_new ("INSERT INTO midgard_user (login, password, user_type, auth_type, auth_type_id, guid, person_guid, active)");
		g_string_append_printf (query, "VALUES ('%s', '%s', %d, '%s', %d, '%s', '%s', %d)",
				ADMIN_USER_LOGIN, ADMIN_USER_PASSWORD,
				MIDGARD_USER_TYPE_ADMIN, DEFAULT_AUTH_TYPE, 
				midgard_core_auth_type_id_from_name (mgd, DEFAULT_AUTH_TYPE), 
				ADMIN_USER_GUID, ADMIN_PERSON_GUID, 1);
		
		sql = query->str;
		midgard_core_query_execute(mgd, sql, TRUE);
		g_string_free (query, TRUE);
	}

	/* quota table */
	MidgardObjectClass *quota_klass = 
		MIDGARD_OBJECT_GET_CLASS_BY_NAME("midgard_quota");
	midgard_storage_create_class_storage(mgd, MIDGARD_DBOBJECT_CLASS(quota_klass));

	/* Those below are important for legacy authentication. Backward compatibility FIXME */
	/* person table */
	MidgardObjectClass *person_klass = 
		MIDGARD_OBJECT_GET_CLASS_BY_NAME("midgard_person");
	midgard_storage_create_class_storage(mgd, MIDGARD_DBOBJECT_CLASS(person_klass));

	/* member table */
	MidgardObjectClass *member_klass = 
		MIDGARD_OBJECT_GET_CLASS_BY_NAME("midgard_member");
	midgard_storage_create_class_storage(mgd, MIDGARD_DBOBJECT_CLASS(member_klass));

	sql = "SELECT lastname, firstname FROM person WHERE guid='f6b665f1984503790ed91f39b11b5392'";

	model = midgard_core_query_get_model(mgd, sql);

	if(model)
		ret_rows = gda_data_model_get_n_rows(model);

	if(!model || ret_rows == 0) {
		
		/* midgard_person record */
		sql = "INSERT INTO person (guid, birthdate, homepage, email, extra, "
			"metadata_creator, lastname, firstname, metadata_created, metadata_revision, username, password ) "
			"VALUES ('f6b665f1984503790ed91f39b11b5392', '1999-05-18 14:40:01', "
			"'http://www.midgard-project.org', 'dev@lists.midgard-project.org', "
			"'Default administrator account for Midgard', 'f6b665f1984503790ed91f39b11b5392', "
			"'Administrator', 'Midgard', '1999-05-18 14:40:01', 1, '', '')";
		
		midgard_core_query_execute(mgd, sql, TRUE);

		/* Create root's repligard entry */
		sql = "INSERT INTO repligard (guid, typename, object_action) "
			"VALUES ('f6b665f1984503790ed91f39b11b5392', 'midgard_person', 0)";
		midgard_core_query_execute(mgd, sql, TRUE);		
	}

	if(model)
		g_object_unref(model);

	return TRUE;
}

/**
 * midgard_storage_create_class_storage:
 * @mgd: #MidgardConnection instance
 * @klass: #MidgardDBObjectClass pointer
 * 
 * Creates underlying storage (e.g. table in database) for given @klass.
 * Given @klass can be any #MidgardDBObjectClass derived one. 
 * It may be class which represents any underlying storage type. 
 * For example, database table or view.
 *
 * If underlying storage already exists, this method silently ignore creation
 * and returns %TRUE. Such case is not considered an error.
 *
 * This method also creates metadata storage if given class uses such.
 * 
 * Indexes are created if:
 * <itemizedlist>
 * <listitem><para>
 * property is a link type
 * </para></listitem>
 * <listitem><para>
 * property is linked to another property
 * </para></listitem>
 * <listitem><para>
 * property is either parent or up
 * </para></listitem>
 * <listitem><para>
 * property holds guid value
 * </para></listitem>
 * </itemizedlist>    
 *    
 * Auto increment (and primary key ) field is created if property is defined 
 * as primaryproperty, and it's integer ( or unsigned one ) type
 *
 * Returns: %TRUE on success, %FALSE otherwise
 *
 * Since: 9.09
 */
gboolean 
midgard_storage_create_class_storage (MidgardConnection *mgd, MidgardDBObjectClass *klass)
{
	g_assert(mgd != NULL);
	g_assert(klass != NULL);

	g_return_val_if_fail(MIDGARD_IS_DBOBJECT_CLASS (klass), FALSE);

	if (klass->dbpriv->create_storage == NULL)
		return FALSE;

	return klass->dbpriv->create_storage(mgd, klass);
}

/**
 * midgard_storage_update_class_storage:
 * @mgd: #MidgardConnection instance
 * @klass: #MidgardDBObjectClass pointer
 *
 * Update underlying storage, which is used by given @klass.
 * 
 * This method doesn't create storage. It creates new columns if are defined
 * for @klass properties and do not exist in storage yet.
 *
 * See midgard_storage_create_class_storage() if you need more info about indexes.
 *
 * Returns: %TRUE on success, %FALSE otherwise
 *
 * Since: 9.09
 */
gboolean 
midgard_storage_update_class_storage (MidgardConnection *mgd, MidgardDBObjectClass *klass)
{
	g_assert(mgd != NULL);
	g_assert(klass != NULL);

	g_return_val_if_fail(MIDGARD_IS_DBOBJECT_CLASS (klass), FALSE);

	if (klass->dbpriv->update_storage == NULL)
		return FALSE;

	return klass->dbpriv->update_storage(mgd, klass);
}

/**
 * midgard_storage_class_storage_exists:
 * @mgd: #MidgardConnection instance
 * @klass: #MidgardDBObjectClass pointer
 *
 * Checks whether storage for given @klass exists.
 *
 * Returns: %TRUE if storage exists, %FALSE otherwise
 *
 * Since: 9.09
 */ 
gboolean 
midgard_storage_class_storage_exists (MidgardConnection *mgd, MidgardDBObjectClass *klass)
{
	g_assert(mgd != NULL);
	g_assert(klass != NULL);

	g_return_val_if_fail(MIDGARD_IS_DBOBJECT_CLASS (klass), FALSE);

	if (klass->dbpriv->storage_exists == NULL)
		return FALSE;

	return klass->dbpriv->storage_exists(mgd, klass);
}

/**
 * midgard_storage_delete_class_storage:
 * @mgd: #MidgardConnection instance
 * @klass: #MidgardDBObjectClass pointer
 * 
 * Delete storage for given @klass.
 * 
 * Returns: %TRUE on success, %FALSE otherwise
 *
 * Since: 9.09
 */ 
gboolean midgard_storage_delete_class_storage (MidgardConnection *mgd, MidgardDBObjectClass *klass)
{
	g_assert(mgd != NULL);
	g_assert(klass != NULL);

	g_return_val_if_fail(MIDGARD_IS_DBOBJECT_CLASS (klass), FALSE);

	if (klass->dbpriv->delete_storage == NULL)
		return FALSE;

	return klass->dbpriv->delete_storage(mgd, klass);
}

/* OBJECT ROUTINES */

GType	
midgard_storage_get_type(void)
{
	static GType type = 0;

	if (type == 0) {

		static const GTypeInfo info = {

			sizeof (MidgardStorageClass),
			NULL,           /* base_init */
			NULL,           /* base_finalize */
			NULL,		/* class init */ 
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof (MidgardStorage),
			0,              /* n_preallocs */  
			NULL
		};

		type = g_type_register_static (G_TYPE_OBJECT,
				"midgard_storage", &info, 0);
	}
	return type;
}
