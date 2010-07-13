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

#ifndef MIDGARD_QUERY_SELECT_SIMPLE_H
#define MIDGARD_QUERY_SELECT_SIMPLE_H

#include <glib-object.h>
#include "midgard_connection.h"
#include "midgard_dbobject.h"

G_BEGIN_DECLS

MidgardDBObject	*midgard_query_select_simple_get_object	(MidgardConnection *mgd, const gchar *classname, const gchar *property, ...); 

G_END_DECLS

#endif /* MIDGARD_QUERY_SELECT_SIMPLE_H */
