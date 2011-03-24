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

#ifndef MIDGARD_WORKSPACE_STORAGE_H
#define MIDGARD_WORKSPACE_STORAGE_H

#include "midgard_dbobject.h"

G_BEGIN_DECLS

/* convention macros */
#define MIDGARD_TYPE_WORKSPACE_STORAGE (midgard_workspace_storage_get_type())
#define MIDGARD_WORKSPACE_STORAGE(object) (G_TYPE_CHECK_INSTANCE_CAST ((object),MIDGARD_TYPE_WORKSPACE_STORAGE, MidgardWorkspaceStorage))
#define MIDGARD_IS_WORKSPACE_STORAGE(object) (G_TYPE_CHECK_INSTANCE_TYPE ((object), MIDGARD_TYPE_WORKSPACE_STORAGE))
#define MIDGARD_WORKSPACE_STORAGE_GET_INTERFACE(inst) (G_TYPE_INSTANCE_GET_INTERFACE ((inst), MIDGARD_TYPE_WORKSPACE_STORAGE, MidgardWorkspaceStorageIFace))

typedef struct _MidgardWorkspaceStorage MidgardWorkspaceStorage; /* dummy */
typedef struct _MidgardWorkspaceStorageIFace MidgardWorkspaceStorageIFace;
typedef struct _MidgardWorkspaceStorageIFacePrivate MidgardWorkspaceStorageIFacePrivate; 

struct _MidgardWorkspaceStorageIFace{
	GTypeInterface parent;	
	MidgardWorkspaceStorageIFacePrivate *priv;

	const gchar		*(*get_path)		(MidgardWorkspaceStorage *self);
	gboolean 		(*get_by_path)		(MidgardWorkspaceStorage *self, const gchar *path, GError **error);
};

/* WorkspaceStorage error */
typedef enum {
	MIDGARD_WORKSPACE_STORAGE_ERROR_NAME_EXISTS,
	MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_PATH,
	MIDGARD_WORKSPACE_STORAGE_ERROR_PATH_EXISTS,
	MIDGARD_WORKSPACE_STORAGE_ERROR_OBJECT_NOT_EXISTS,
	MIDGARD_WORKSPACE_STORAGE_ERROR_INVALID_VALUE,
	MIDGARD_WORKSPACE_STORAGE_ERROR_CONTEXT_VIOLATION
} MidgardWorkspaceStorageError;

#define MIDGARD_WORKSPACE_STORAGE_ERROR midgard_workspace_storage_error_quark ()

GType			midgard_workspace_storage_get_type		(void);
const gchar 		*midgard_workspace_storage_get_path		(MidgardWorkspaceStorage *self);
gboolean		midgard_workspace_storage_get_by_path		(MidgardWorkspaceStorage *self, const gchar *path, GError **error);

G_END_DECLS

#endif /* MIDGARD_WORKSPACE_STORAGE_H */
