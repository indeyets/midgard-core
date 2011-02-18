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
	g_object_set (workspace, "name", "MyFirstWorkspace", NULL);
	GError *error = NULL;
	gboolean workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == TRUE);
	g_assert (error == NULL);

	MidgardWorkspace *second_workspace = midgard_workspace_new (mgd, workspace);
	g_object_set (second_workspace, "name", "MySecondWorkspace", NULL);
	error = NULL;
	gboolean second_workspace_created = midgard_workspace_create (second_workspace, &error);
	g_assert (second_workspace_created == TRUE);
	g_assert (error == NULL);

	g_object_unref (workspace);
	g_object_unref (second_workspace);

	/* FAIL */

	/* Empty Name */
	workspace = midgard_workspace_new (mgd, NULL);
	error = NULL;
	workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE);
	g_object_unref (workspace);

	/* Name exists */
	workspace = midgard_workspace_new (mgd, NULL);
	g_object_set (workspace, "name", MGD_TEST_WORKSPACE_NAME_STABLE, NULL);
	error = NULL;
	workspace_created = midgard_workspace_create (workspace, &error);
	g_assert (workspace_created == FALSE);
	g_assert (error != NULL);
	g_assert (error->code == MIDGARD_WORKSPACE_STORAGE_ERROR_NAME_EXISTS);
	g_object_unref (workspace);

	/* Invalid parent workspace */

}

void 
midgard_test_workspace_get_by_path (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
}

void 
midgard_test_workspace_list_children (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
}

void 
midgard_test_workspace_get_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
}

void 
midgard_test_workspace_is_in_context (MidgardWorkspaceTest *mwt, gconstpointer data)
{
	MidgardConnection *mgd = mwt->mgd;
}


