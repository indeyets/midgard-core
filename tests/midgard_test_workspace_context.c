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

#include "midgard_test.h"

void 
midgard_test_workspace_context_create (MidgardWorkspaceContextTest *mwct, gconstpointer data)
{
	MidgardConnection *mgd = mwct->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspaceContext *workspace_context = midgard_workspace_context_new ();
	g_assert (workspace_context != NULL);
	g_assert (MIDGARD_IS_WORKSPACE_CONTEXT (workspace_context));
	
	gboolean workspace_context_created = midgard_workspace_manager_create (manager, workspace_context, MGD_TEST_WORKSPACE_PATH, &error);
	g_assert (workspace_created != TRUE);
	g_assert (error == NULL);

	g_object_unref (workspace_context);

	/* FAIL */
	MidgardWorkspaceContext *dummy_context = midgard_workspace_context_new ();
	workspace_context_created = midgard_workspace_manager_create (manager, dummy_context, "", &error);
	g_assert (workspace_context_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_PATH);

	g_object_unref (dummy_context);
	g_clear_error (&error);
}

void 
midgard_test_workspace_context_exists (MidgardWorkspaceContextTest *mwct, gconstpointer data)
{
	MidgardConnection *mgd = mwct->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	gboolean workspace_context_exists = midgard_workspace_manager_path_exists (manager, MGD_TEST_WORKSPACE_CONTEXT_PATH);
	g_assert (workspace_context_exists == TRUE);

	/* FAIL */
	workspace_context_exists = midgard_workspace_manager_path_exists (manager, "/NOT/EXISTS");
	g_assert (workspace_context_exists == FALSE);

	workspace_context_exists = midgard_workspace_manager_path_exists (manager, "//NOT/EXISTS");
	g_assert (workspace_context_exists == FALSE);

	workspace_context_exists = midgard_workspace_manager_path_exists (manager, "");
	g_assert (workspace_context_exists == FALSE);

	workspace_context_exists = midgard_workspace_manager_path_exists (manager, "/");
	g_assert (workspace_context_exists == FALSE);
}

void 
midgard_test_workspace_context_get_path (MidgardWorkspaceContextTest *mwct, gconstpointer data)
{
	MidgardConnection *mgd = mwct->mgd;

	GError *error = NULL;
	MidgardWorkspaceContext *workspace_context_fetched = midgard_workspace_context_create (mgd, MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_context_fetched != NULL);
	g_assert (MIDGARD_IS_WORKSPACE_CONTEXT (workspace_context_fetched));
	g_assert (error == NULL);

	const gchar *workspace_context_path = midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (workspace_context_fetched));
	g_assert (workspace_context_path != NULL);
	g_assert_cmpstr (workspace_context_path,  !=,  "");
	g_assert_cmpstr (workspace_context_path, ==, MGD_TEST_WORKSPACE_CONTEXT_PATH);

	g_object_unref (workspace_context_fetched);
}

void 
midgard_test_workspace_context_list_workspace_names (MidgardWorkspaceContextTest *mwct, gconstpointer data)
{
	MidgardConnection *mgd = mwct->mgd;

	GError *error = NULL;
	MidgardWorkspaceContext *workspace_context_fetched = midgard_workspace_context_create (mgd, MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_context_fetched != NULL);
	g_assert (MIDGARD_IS_WORKSPACE_CONTEXT (workspace_context_fetched));
	g_assert (error == NULL);

	guint n_names;
	gchar **workspace_names = midgard_workspace_context_list_workspace_names (workspace_context_fetched, &n_names);
	g_assert (workspace_names != NULL);
	g_assert_cmpint (n_names, !=, 0);

	g_assert_cmpstr (workspace_names[0], ==, MGD_TEST_WORKSPACE_NAME_STABLE);
	g_assert_cmpstr (workspace_names[1], ==, MGD_TEST_WORKSPACE_NAME_TESTING);
	g_assert_cmpstr (workspace_names[2], ==, MGD_TEST_WORKSPACE_NAME_PRIVATE);

	g_object_unref (workspace_context_fetched);
	g_free (workspace_names);
}

void 
midgard_test_workspace_context_get_workspace_by_name (MidgardWorkspaceContextTest *mwct, gconstpointer data)
{
	MidgardConnection *mgd = mwct->mgd;

	GError *error = NULL;
	MidgardWorkspaceContext *workspace_context = midgard_workspace_context_create (mgd, MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_context != NULL);
	g_assert (MIDGARD_IS_WORKSPACE_CONTEXT (workspace_context));
	g_assert (error == NULL);

	MidgardWorkspace *workspace = midgard_workspace_context_get_workspace_by_name (workspace_context, MGD_TEST_WORKSPACE_NAME_STABLE);
	g_assert (workspace != NULL);
	g_object_unref (workspace);

	workspace = midgard_workspace_context_get_workspace_by_name (workspace_context, MGD_TEST_WORKSPACE_NAME_TESTING);
	g_assert (workspace != NULL);
	g_object_unref (workspace);

	workspace = midgard_workspace_context_get_workspace_by_name (workspace_context, MGD_TEST_WORKSPACE_NAME_PRIVATE);
	g_assert (workspace != NULL);
	g_object_unref (workspace);

	g_object_unref (workspace_context);
}
