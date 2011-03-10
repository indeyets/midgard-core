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

void 
midgard_test_object_workspace_create (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
        const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
        g_assert (manager != NULL);

	MidgardWorkspace *workspace = midgard_workspace_new ();
	GError *error = NULL;
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, workspace, MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);

	midgard_connection_set_workspace (mgd, workspace);
	midgard_connection_enable_workspace (mgd);
	g_assert (midgard_connection_is_enabled_workspace (mgd) == TRUE);

	MidgardObject *person = midgard_object_new (mgd, _OBJECT_CLASS, NULL);
	g_object_set (person, "firstname", "Sir Lancelot", NULL);
	gboolean object_created = midgard_object_create (person);
	g_assert (object_created == TRUE);

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
}

void 
midgard_test_object_workspace_update (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

void 
midgard_test_object_workspace_select (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

void 
midgard_test_object_workspace_delete (MidgardObjectWorkspaceTest *mwt, gconstpointer data)
{
	g_print (MISS_IMPL);
}

