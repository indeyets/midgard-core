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
	MidgardConnection *mgd = mwt->mgd;

	MidgardWorkspace *parent_workspace = midgard_workspace_new (mgd, NULL);
	g_assert (parent_workspace != NULL);

	MidgardWorkspace *workspace = midgard_workspace_new (mgd, parent_workspace);
	g_assert (workspace != NULL);

	g_object_unref (parent_workspace);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_create (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;

	MidgardWorkspace *workspace = midgard_workspace_new (mgd, NULL);
	g_object_set (workspace, "name", _FIRST_WS_NAME, NULL);
	GError *error = NULL;
	gboolean workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == TRUE);
	g_assert (error == NULL);

	MidgardWorkspace *second_workspace = midgard_workspace_new (mgd, workspace);
	g_object_set (second_workspace, "name", _SECOND_WS_NAME, NULL);
	error = NULL;
	gboolean second_workspace_created = midgard_workspace_create (second_workspace, &error);
	g_assert (second_workspace_created == TRUE);
	g_assert (error == NULL);

	g_object_unref (workspace);
	g_object_unref (second_workspace);

	/* FAIL */

	/* Empty Name */
	workspace = midgard_workspace_new (mgd, NULL);
	workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE);
	g_object_unref (workspace);
	g_clear_error (&error);

	/* Name exists */
	workspace = midgard_workspace_new (mgd, NULL);
	g_object_set (workspace, "name", MGD_TEST_WORKSPACE_NAME_STABLE, NULL);
	workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_NAME_EXISTS);
	g_object_unref (workspace);
	g_clear_error (&error);

	/* Invalid parent workspace */
	MidgardWorkspace *workspace_a = midgard_workspace_new (mgd, NULL);
	g_assert (workspace_a != NULL);
	workspace = midgard_workspace_new (mgd, workspace_a);
	g_assert (workspace != NULL);
	workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE);

	g_object_unref (workspace_a);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_get_by_path (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	gboolean got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);
	g_object_unref (workspace);

	workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), "/MyFirstWorkspace", &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);
	g_object_unref (workspace);

	/* FAIL */
	/* Path doesn't exist */
	workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), "/NOT/EXISTS", &error);
	g_assert (got_by_path == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_OBJECT_NOT_EXISTS);
	g_clear_error (&error);
	g_object_unref (workspace);

	/* Path is invalid */
	workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), "", &error);
	g_assert (got_by_path == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_PATH);
	g_object_unref (workspace);
}

void 
midgard_test_workspace_list_children (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	gboolean got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);

	//MidgardWorkspace **children = midgard_workspace_

	g_object_unref (workspace);



}

void 
midgard_test_workspace_get_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new (mgd, NULL);
	g_assert (workspace != NULL);
	gboolean got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (workspace != NULL);
	g_assert (error == NULL);

	MidgardWorkspaceContext *ws_ctx = midgard_workspace_get_context (workspace);
	g_assert (ws_ctx != NULL);

	MidgardWorkspaceContext *ctx = midgard_workspace_context_create (mgd, MGD_TEST_WORKSPACE_CONTEXT_PATH, NULL);
	g_assert (ctx != NULL);

	g_assert_cmpstr (midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (ws_ctx)), ==, midgard_workspace_storage_get_path (MIDGARD_WORKSPACE_STORAGE (ctx)));

	g_object_unref (workspace);
	g_object_unref (ws_ctx);
	g_object_unref (ctx);
}

void 
midgard_test_workspace_is_in_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;

	GError *error = NULL;
	MidgardWorkspace *workspace = midgard_workspace_new (mgd, NULL);
	gboolean got_by_path = midgard_workspace_storage_get_by_path (MIDGARD_WORKSPACE_STORAGE (workspace), MGD_TEST_WORKSPACE_CONTEXT_PATH, &error);
	g_assert (got_by_path == TRUE);
	g_assert (error == NULL);

	MidgardWorkspaceContext *ws_ctx = midgard_workspace_get_context (workspace);
	g_assert (ws_ctx != NULL);

	MidgardWorkspaceContext *ctx = midgard_workspace_context_create (mgd, MGD_TEST_WORKSPACE_CONTEXT_PATH, NULL);
	g_assert (ctx != NULL);

	g_assert (midgard_workspace_is_in_context (workspace, ws_ctx) == TRUE);
	g_assert (midgard_workspace_is_in_context (workspace, ctx) == TRUE);

	g_object_unref (workspace);
	g_object_unref (ws_ctx);
	g_object_unref (ctx);
}
