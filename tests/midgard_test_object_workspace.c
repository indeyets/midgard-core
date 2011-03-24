/* 
 * Copyright (C) 2011 Piotr Pokora <piotrek.pokora@gmail.com>
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

#include "midgard_test_object_workspace.h"

#define _OBJECT_CLASS "midgard_person"
#define _NAME_LANCELOT "Sir Lancelot"
#define _NAME_ARTHUR "King Arthur"

gchar *lancelot_guid = NULL;
gchar *arthur_guid = NULL;

void 
midgard_test_object_workspace_create (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
        const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
        g_assert (manager != NULL);

	MidgardWorkspace *workspace = midgard_workspace_new ();
	GError *error = NULL;
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);

	midgard_connection_set_workspace (mgd, MIDGARD_WORKSPACE_STORAGE (workspace));
	midgard_connection_enable_workspace (mgd, TRUE);
	g_assert (midgard_connection_is_enabled_workspace (mgd) == TRUE);

	gboolean storage_updated = midgard_storage_update (mgd, _OBJECT_CLASS);
	g_assert (storage_updated == TRUE);

	MidgardObject *person = midgard_object_new (mgd, _OBJECT_CLASS, NULL);
	g_object_set (person, "firstname", _NAME_ARTHUR, NULL);
	gboolean object_created = midgard_object_create (person);
	MIDGARD_TEST_ERROR_OK(mgd);
	g_assert (object_created == TRUE);

	/* Keep Arthur's guid */
	g_object_get (person, "guid", &arthur_guid, NULL);

	MidgardWorkspace *object_workspace = midgard_object_get_workspace (person);
	g_assert (object_workspace != NULL);

	gchar *ws_name;
	gchar *object_ws_name;

	g_object_get (workspace, "name", &ws_name, NULL);
	g_object_get (object_workspace, "name", &object_ws_name, NULL);

	g_assert_cmpstr (ws_name, ==, object_ws_name);

	g_free (ws_name);
	g_free (object_ws_name);

	g_object_unref (workspace);
	g_object_unref (person);
	g_object_unref (object_workspace);

	workspace = midgard_workspace_new ();
	error = NULL;
	get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_PATH, &error);
	g_assert (get_by_path == TRUE);

	midgard_connection_set_workspace (mgd, MIDGARD_WORKSPACE_STORAGE (workspace));
	midgard_connection_enable_workspace (mgd, TRUE);
	g_assert (midgard_connection_is_enabled_workspace (mgd) == TRUE);

	person = midgard_object_new (mgd, _OBJECT_CLASS, NULL);
	g_object_set (person, "firstname", _NAME_LANCELOT, NULL);
	object_created = midgard_object_create (person);
	MIDGARD_TEST_ERROR_OK(mgd);
	g_assert (object_created == TRUE);

	/* Keep Lancelot's guid */
	g_object_get (person, "guid", &lancelot_guid, NULL);

	object_workspace = midgard_object_get_workspace (person);
	g_assert (object_workspace != NULL);

	g_object_get (workspace, "name", &ws_name, NULL);
	g_object_get (object_workspace, "name", &object_ws_name, NULL);

	g_assert_cmpstr (ws_name, ==, object_ws_name);

	g_free (ws_name);
	g_free (object_ws_name);

	g_object_unref (workspace);
	g_object_unref (person);
	g_object_unref (object_workspace);
}

void 
midgard_test_object_workspace_select_created (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
        const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
        g_assert (manager != NULL);

	MidgardWorkspace *workspace = midgard_workspace_new ();
	GError *error = NULL;
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);

	midgard_connection_set_workspace (mgd, MIDGARD_WORKSPACE_STORAGE (workspace));
	midgard_connection_enable_workspace (mgd, TRUE);
	g_assert (midgard_connection_is_enabled_workspace (mgd) == TRUE);

	/* Get Arthur person */
	GValue gval = {0, };
	g_value_init (&gval, G_TYPE_STRING);
	g_value_set_string (&gval, arthur_guid);
	MidgardObject *person = midgard_object_new (mgd, _OBJECT_CLASS, &gval);
	g_value_unset (&gval);

	g_assert (person != NULL);
	MIDGARD_TEST_ERROR_OK(mgd);
	
	MidgardWorkspace *object_workspace = midgard_object_get_workspace (person);
	g_assert (object_workspace != NULL);

	gchar *ws_name;
	gchar *object_ws_name;

	g_object_get (workspace, "name", &ws_name, NULL);
	g_object_get (object_workspace, "name", &object_ws_name, NULL);

	g_assert_cmpstr (ws_name, ==, object_ws_name);

	g_free (ws_name);
	g_free (object_ws_name);

	g_object_unref (workspace);
	g_object_unref (object_workspace);
	g_object_unref (person);

	workspace = midgard_workspace_new ();
	error = NULL;
	get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_PATH, &error);
	g_assert (get_by_path == TRUE);

	midgard_connection_set_workspace (mgd, MIDGARD_WORKSPACE_STORAGE (workspace));
	midgard_connection_enable_workspace (mgd, TRUE);
	g_assert (midgard_connection_is_enabled_workspace (mgd) == TRUE);

	/* Get Lancelot person */
	g_value_init (&gval, G_TYPE_STRING);
	g_value_set_string (&gval, lancelot_guid);
	person = midgard_object_new (mgd, _OBJECT_CLASS, &gval);
	g_value_unset (&gval);

	g_assert (person != NULL);
	MIDGARD_TEST_ERROR_OK(mgd);

	object_workspace = midgard_object_get_workspace (person);
	g_assert (object_workspace != NULL);

	g_object_get (workspace, "name", &ws_name, NULL);
	g_object_get (object_workspace, "name", &object_ws_name, NULL);

	g_assert_cmpstr (ws_name, ==, object_ws_name);

	g_free (ws_name);
	g_free (object_ws_name);

	g_object_unref (workspace);
	g_object_unref (object_workspace);
	g_object_unref (person);
}

void 
midgard_test_object_workspace_update (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

void 
midgard_test_object_workspace_select_updated (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

void 
midgard_test_object_workspace_delete (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

