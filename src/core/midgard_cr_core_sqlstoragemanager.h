/* MidgardCore SQLStorageManager routines
 *    
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

#ifndef _MIDGARD_CR_CORE_SQL_STORAGE_MANAGER_H_
#define _MIDGARD_CR_CORE_SQL_STORAGE_MANAGER_H_

#include "midgard_local.h"
#include <glib.h>

struct _MidgardCRSQLTableModel;
struct _MidgardCRStorageManager;
struct _MidgardCRSQLStorageManager;
struct _MidgardCRSQLColumnModel;

/* Helper macros */

#define MIDGARD_CR_CORE_MANAGER_UPDATE_PROFILER(__manager, __query) \
	if (__manager->_profiler) { \
		if (__manager->_profiler->_enabled) { \
			g_free (__manager->_profiler->_command); \
			__manager->_profiler->_command = g_strdup (__query); \
		} \
	}

#define __STORAGE_MANAGER_UPDATE_PROFILER_WITH_STMT(__manager, __stmt, __set) \
	if (__manager->_profiler && __manager->_profiler->_enabled) { \
		GError *__err = NULL; \
		gchar *debug_sql = gda_connection_statement_to_sql (GDA_CONNECTION (__manager->_cnc), __stmt, __set, GDA_STATEMENT_SQL_PRETTY, NULL, &__err); \
		if (__err) g_warning ("%s error: %s", G_OBJECT_TYPE_NAME (__manager), __err->message ? __err->message : "Unknown reason"); \
		g_clear_error (&__err); \
		g_free (__manager->_profiler->_command); \
		__manager->_profiler->_command = debug_sql; \
	}

gboolean midgard_cr_core_sql_storage_manager_open (struct _MidgardCRSQLStorageManager *manager, GError **error);
gboolean midgard_cr_core_sql_storage_manager_close (struct _MidgardCRSQLStorageManager *manager, GError **error);
gboolean midgard_cr_core_sql_storage_manager_initialize_storage (struct _MidgardCRSQLStorageManager *manager, GError **error);

/* SQLTableModel methods */ 
gboolean midgard_cr_core_sql_storage_manager_table_exists (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLTableModel *storage_model);
void midgard_cr_core_sql_storage_manager_table_create (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLTableModel *storage_model, GError **error);
void midgard_cr_core_sql_storage_manager_table_remove (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLTableModel *storage_model, GError **error);

/* SQLColumnModel methods */
gboolean midgard_cr_core_sql_storage_manager_column_exists (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLColumnModel *property_model);
void midgard_cr_core_sql_storage_manager_column_create (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLColumnModel *property_model, GError **error);
void midgard_cr_core_sql_storage_manager_column_update (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLColumnModel *property_model, GError **error);
void midgard_cr_core_sql_storage_manager_column_remove (struct _MidgardCRSQLStorageManager *manager, struct _MidgardCRSQLColumnModel *property_model, GError **error);

/* QUERY */
gint midgard_cr_core_sql_storage_manager_query_execute (struct _MidgardCRSQLStorageManager *manager, const gchar *query, GError **error);

/* MODELS */
void midgard_cr_core_sql_storage_manager_load_models (struct _MidgardCRSQLStorageManager *self, GError **error);

#endif /* _MIDGARD_CR_CORE_SQL_STORAGE_MANAGER_H_ */
