/* 
 * Copyright (C) 2010 Piotr Pokora <piotrek.pokora@gmail.com>
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

#include "midgard_workspace_storage.h"
#include "midgard_core_object.h"

GQuark
midgard_workspace_storage_error_quark (void)
{
	return g_quark_from_static_string ("midgard_workspace_storage_error-quark");
}

/**
 * midgard_workspace_storage_get_path:
 * @self: #MidgardWorspaceStorage instance
 *
 * Returned path may be %NULL, if given object doesn't exists in storage
 *
 * Returns: (transfer none): a path, given #MidgardWorkspaceStorage is at.
 * Since: 10.05.4
 */
const gchar *
midgard_workspace_storage_get_path (MidgardWorkspaceStorage *self)
{
	g_return_val_if_fail (self != NULL, NULL);

	return MIDGARD_WORKSPACE_STORAGE_GET_INTERFACE (self)->get_path (self);
}


/**
 * midgard_workspace_storage_get_by_path:
 * @self: #MidgardWorkspaceStorage instance
 * @path: a path #MidgardWorkspaceStorage object should be found at (e.g. /Organization/Users/John)
 * @error: a pointer to store returned error
 * 
 * Cases to return %NULL:
 * <itemizedlist>
 * <listitem><para>
 * Given path is invalid ( MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_PATH )
 * </para></listitem>
 * <listitem><para>
 * WorkspaceStorageStorage at given path doesn't exist ( MIDGARD_WORKSPACE_STORAGE_ERROR_OBJECT_NOT_EXISTS )
 * </para></listitem>
 * </itemizedlist>
 *
 * Returns: %TRUE if workspace is found at given path, %FALSE otherwise
 * Since: 10.05.4
 */
gboolean
midgard_workspace_storage_get_by_path (MidgardWorkspaceStorage *self, const gchar *path, GError **error)
{
	g_return_val_if_fail (self != NULL, FALSE);
	MidgardConnection *mgd = MGD_OBJECT_CNC (self);
	g_return_val_if_fail (mgd != NULL, FALSE);

	return MIDGARD_WORKSPACE_STORAGE_GET_INTERFACE (self)->get_by_path (self, path, error);
}

GType
midgard_workspace_storage_get_type (void)
{
	static GType type = 0;
	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (MidgardWorkspaceStorageIFace),
			NULL,   /* base_init */
			NULL,   /* base_finalize */
			NULL,   /* class_init */
			NULL,   /* class_finalize */
			NULL,   /* class_data */
			0,
			0,      /* n_preallocs */
			NULL    /* instance_init */
		};
		type = g_type_register_static (G_TYPE_INTERFACE, "MidgardWorkspaceStorage", &info, 0);
		g_type_interface_add_prerequisite (type, G_TYPE_OBJECT);
	}
	return type;
}
