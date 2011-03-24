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

#define _FIRST_WS_NAME "MyFirstWorkspace"
#define _SECOND_WS_NAME "MySecondWorkspace"

void 
midgard_test_workspace_new (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);

	g_object_unref (workspace);
}

void 
midgard_test_workspace_create (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_object_set (workspace, "name", MGD_TEST_WORKSPACE_NAME_LANCELOT, NULL);
	GError *error = NULL;
	gboolean workspace_created = midgard_workspace_manager_create (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_created == TRUE);
	g_assert (error == NULL);
	g_object_unref (workspace);

	/* FAIL */

	/* Empty Name */
	workspace = midgard_workspace_new ();
	g_object_set (workspace, "name", "", NULL);
	workspace_created = midgard_workspace_manager_create (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE);
	g_clear_error (&error);
	g_object_unref (workspace);

	/* Name exists */
	workspace = midgard_workspace_new ();
	g_object_set (workspace, "name", MGD_TEST_WORKSPACE_NAME_LANCELOT, NULL);
	workspace_created = midgard_workspace_manager_create (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_NAME_EXISTS);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_update (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gboolean got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);

	gboolean workspace_updated = midgard_workspace_manager_update (manager, MIDGARD_WORKSPACE_STORAGE (workspace), &error);
	if (error)
		g_assert_cmpstr (error->message, ==, "");
	g_assert (workspace_updated == TRUE);
	g_assert (error == NULL);

	g_object_unref (workspace);	

	/* FAIL */
	workspace = midgard_workspace_new ();
	/* Invalid ID */
	workspace_updated = midgard_workspace_manager_update (manager, MIDGARD_WORKSPACE_STORAGE (workspace), &error);
	g_assert (workspace_updated == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE);
	g_clear_error (&error);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_exists (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	gchar *ws_path = g_strdup_printf ("%s/%s", MGD_TEST_WORKSPACE_CONTEXT_PATH, MGD_TEST_WORKSPACE_NAME_LANCELOT);
	gboolean workspace_exists = midgard_workspace_manager_path_exists (manager, ws_path);
	g_assert (workspace_exists == TRUE);
	g_free (ws_path);
}

void 
midgard_test_workspace_purge (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	g_print ("purge: %s \n", MISS_IMPL);
}

void 
midgard_test_workspace_get_by_path (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gboolean got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);
	g_object_unref (workspace);

	workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gchar *ws_path = g_strdup_printf ("%s/%s", MGD_TEST_WORKSPACE_CONTEXT_PATH, MGD_TEST_WORKSPACE_NAME_LANCELOT);
	got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), ws_path, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);
	g_object_unref (workspace);
	g_free (ws_path);

	/* FAIL */
	/* Path doesn't exist */
	workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), "/NOT/EXISTS", &error);
	g_assert (got_by_path == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_OBJECT_NOT_EXISTS);
	g_clear_error (&error);
	g_object_unref (workspace);

	/* Path is invalid */
	workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), "", &error);
	g_assert (got_by_path == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_PATH);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_get_path (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gchar *ws_path = g_strdup_printf ("%s/%s", MGD_TEST_WORKSPACE_CONTEXT_PATH, MGD_TEST_WORKSPACE_NAME_LANCELOT);
	gboolean got_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), ws_path, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);

	const gchar *path = midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (workspace));
	g_assert_cmpstr (path, ==, ws_path);

	g_object_unref (workspace);
	g_free (ws_path);

	workspace = midgard_workspace_new ();
	path = midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (workspace));
	g_assert_cmpstr (path, ==, NULL); 
}

void 
midgard_test_workspace_list_workspace_names (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	g_print ("list_workspace_names: %s \n", MISS_IMPL);
}

void 
midgard_test_workspace_get_workspace_by_name (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	g_print ("get_workspace_by_name: %s \n", MISS_IMPL);
}

void 
midgard_test_workspace_list_children (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);
	g_assert (error == NULL);

	//MidgardWorkspace **children = midgard_workspace_
	g_print ("list_children: %s \n", MISS_IMPL);

	g_object_unref (workspace);
}

void 
midgard_test_workspace_get_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);
	g_assert (error == NULL);

	const MidgardWorkspaceContext *ws_ctx = midgard_workspace_get_context (workspace);
	g_assert (ws_ctx != NULL);

	MidgardWorkspaceContext *ctx = midgard_workspace_context_new ();
	g_assert (ctx != NULL);
	get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (ctx), MGD_TEST_WORKSPACE_CONTEXT_PATH, NULL);
	g_assert (get_by_path == TRUE);

	g_assert_cmpstr (midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (ws_ctx)), ==, midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (ctx)));

	g_object_unref (workspace);
	g_object_unref (G_OBJECT (ws_ctx));
	g_object_unref (ctx);
}

void 
midgard_test_workspace_is_in_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
	const MidgardWorkspaceManager *manager = midgard_connection_get_workspace_manager (mgd);
	g_assert (manager != NULL);

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new ();
	g_assert (workspace != NULL);
	gboolean get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (get_by_path == TRUE);
	g_assert (error == NULL);

	const MidgardWorkspaceContext *ws_ctx = midgard_workspace_get_context (workspace);
	g_assert (ws_ctx != NULL);

	MidgardWorkspaceContext *ctx = midgard_workspace_context_new ();
	g_assert (ctx != NULL);
	get_by_path = midgard_workspace_manager_get_workspace_by_path (manager, MIDGARD_WORKSPACE_STORAGE (ctx), MGD_TEST_WORKSPACE_CONTEXT_PATH, NULL);
	g_assert (get_by_path == TRUE);

	g_assert (midgard_workspace_is_in_context (workspace, ws_ctx) == TRUE);
	g_assert (midgard_workspace_is_in_context (workspace, ctx) == TRUE);

	g_object_unref (workspace);
	g_object_unref (ws_ctx);
	g_object_unref (ctx);
}
