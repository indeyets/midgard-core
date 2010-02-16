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

#ifndef MIDGARD_QUERY_PROPERTY_H
#define MIDGARD_QUERY_PROPERTY_H

#include <glib-object.h>
#include "midgard_defs.h"

G_BEGIN_DECLS

/* convention macros */
#define MIDGARD_QUERY_PROPERTY_TYPE (midgard_query_property_get_type()) 
#define MIDGARD_QUERY_PROPERTY(object)  (G_TYPE_CHECK_INSTANCE_CAST ((object),MIDGARD_QUERY_PROPERTY_TYPE, MidgardQueryProperty))
#define MIDGARD_QUERY_PROPERTY_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_QUERY_PROPERTY_TYPE, MidgardQueryPropertyClass))
#define MIDGARD_IS_QUERY_PROPERTY(object) (G_TYPE_CHECK_INSTANCE_TYPE ((object), MIDGARD_QUERY_PROPERTY_TYPE))
#define MIDGARD_IS_QUERY_PROPERTY_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_QUERY_PROPERTY_TYPE))
#define MIDGARD_QUERY_PROPERTY_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_QUERY_PROPERTY_TYPE, MidgardQueryPropertyClass))

typedef struct _MidgardQueryProperty MidgardQueryProperty;
typedef struct _MidgardQueryPropertyClass MidgardQueryPropertyClass; 

struct _MidgardQueryPropertyClass {
	GObjectClass parent;
};

struct _MidgardQueryProperty {
	GObject parent;
	GValue value;
	MidgardDBObjectClass *klass;
};

GType 			midgard_query_property_get_type		(void);
MidgardQueryProperty	*midgard_query_property_new		(const gchar *propname, const gchar *classname);
const gchar 		*midgard_query_property_get_classname 	(MidgardQueryProperty *self);
gboolean 		midgard_query_property_set_classname	(MidgardQueryProperty *self, const gchar *classname);

G_END_DECLS

#endif /* MIDGARD_QUERY_PROPERTY_H */
