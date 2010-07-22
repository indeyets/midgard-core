/* 
 * Copyright (C) 2007, 2009, 2010 Piotr Pokora <piotrek.pokora@gmail.com>
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

#include "midgard_dbobject.h"
#include "schema.h"
#include "midgard_core_object.h"
#include "midgard_core_object_class.h"
#include <sql-parser/gda-sql-parser.h>

static GObjectClass *parent_class= NULL;

/* Create GdaSqlSelectField for every property registered for the class. */
void
_add_fields_to_select_statement (MidgardDBObjectClass *klass, GdaSqlStatementSelect *select, const gchar *table_name)
{
	guint n_prop;
	guint i;
	GdaSqlSelectField *select_field;
	GdaSqlExpr *expr;
	GValue *val;
	gchar *table_field;
	//GParamSpec **pspecs = g_object_class_list_properties (G_OBJECT_CLASS (klass), &n_prop);
	GParamSpec **pspecs = midgard_core_dbobject_class_list_properties (klass, &n_prop);
	if (!pspecs)
		return;

	const gchar *property_table = NULL;
	for (i = 0; i < n_prop; i++) {

		const gchar *property = pspecs[i]->name;
		const gchar *property_field = midgard_core_class_get_property_colname (klass, property);
		property_table = midgard_core_class_get_property_table (klass, property); 
		if (property_table && table_name)
			property_table = table_name;

		/* Ignore properties with NULL storage and those of object type */
		if (!property_table || pspecs[i]->value_type == G_TYPE_OBJECT)
			continue;

       		select_field = gda_sql_select_field_new (GDA_SQL_ANY_PART (select));
		/*select_field->field_name = g_strdup (property_field);
		select_field->table_name = g_strdup (property_table);*/
		select_field->as = g_strdup (property);
		select->expr_list = g_slist_append (select->expr_list, select_field);
		expr = gda_sql_expr_new (GDA_SQL_ANY_PART (select_field));
		val = g_new0 (GValue, 1);
		g_value_init (val, G_TYPE_STRING);
		table_field = g_strconcat (property_table, ".", property_field, NULL);
		g_value_set_string (val, table_field);
		g_free (table_field);
		expr->value = val;
		select_field->expr = expr;
	}	

	if (!klass->dbpriv->has_metadata)
		return;

	/* Check if metadata provides own method to add fields. If not, use given class storage. */
	if (MIDGARD_IS_OBJECT_CLASS (klass)) {

		MidgardMetadataClass *mklass = MGD_DBCLASS_METADATA_CLASS (klass);
		if (!mklass)
			return;

		if (MIDGARD_DBOBJECT_CLASS (mklass)->dbpriv->add_fields_to_select_statement) {
			MIDGARD_DBOBJECT_CLASS (mklass)->dbpriv->add_fields_to_select_statement (MIDGARD_DBOBJECT_CLASS (mklass), select, table_name);
			return;
		}

		const gchar *table = midgard_core_class_get_table (klass);
		if (table_name)
			table = table_name;

		/* TODO, Once we stabilize use case, refactor this below to minimize code usage */
		GParamSpec **pspecs = g_object_class_list_properties (G_OBJECT_CLASS (mklass), &n_prop);
		if (!pspecs)
			return;
		
		for (i = 0; i < n_prop; i++) {

			const gchar *property = pspecs[i]->name;
			const gchar *property_field = midgard_core_class_get_property_colname (MIDGARD_DBOBJECT_CLASS (mklass), property);	

			if (pspecs[i]->value_type == G_TYPE_OBJECT || !property_field)
				continue;
			
			select_field = gda_sql_select_field_new (GDA_SQL_ANY_PART (select));
			/*select_field->field_name = g_strdup (property_field);
			select_field->table_name = g_strdup (table);*/
			select_field->as = g_strconcat ("metadata_", property, NULL);
			select->expr_list = g_slist_append (select->expr_list, select_field);
			expr = gda_sql_expr_new (GDA_SQL_ANY_PART (select_field));
			val = g_new0 (GValue, 1);
			g_value_init (val, G_TYPE_STRING);
			table_field = g_strconcat (table, ".", property_field, NULL);
			g_value_set_string (val, table_field);
			g_free (table_field);
			expr->value = val;
			select_field->expr = expr;
		}

		g_free (pspecs);
	}

	return;
}

gboolean
_midgard_dbobject_get_property (MidgardDBObject *self, const gchar *name, GValue *value)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	g_return_val_if_fail (G_IS_VALUE (value), FALSE);

	if (!self->dbpriv->datamodel)
		return FALSE;

	GdaDataModel *model = GDA_DATA_MODEL (self->dbpriv->datamodel);
	if (!model || (model && !GDA_IS_DATA_MODEL (model)))
		return FALSE;

	gint col_idx = gda_data_model_get_column_index (model, name);
	if (col_idx == -1)
		return FALSE;

	const GValue *src_val = gda_data_model_get_value_at (model, col_idx, self->dbpriv->row, NULL);
	if (!src_val)
		return FALSE;

	if (!G_IS_VALUE (src_val)) {
		/* NULL fetched from underlying field */
		if (G_VALUE_HOLDS_STRING (value)) {
			g_value_set_string (value, "");
			return TRUE;
		}
		g_warning ("Can not find value for given '%s' property \n", name);
		return FALSE;
	}

	if (G_VALUE_TYPE (src_val) != G_VALUE_TYPE (value))
		g_value_transform (src_val, value);
	else 
		g_value_copy (src_val, value);

	return TRUE;
}

gboolean
_midgard_dbobject_set_property (MidgardDBObject *self, const gchar *name, GValue *value)
{
	g_return_val_if_fail (self != NULL, FALSE);
	g_return_val_if_fail (name != NULL, FALSE);
	g_return_val_if_fail (G_IS_VALUE (value), FALSE);
	
	GdaDataModel *model = GDA_DATA_MODEL (self->dbpriv->datamodel);
	if (!model)
		return FALSE;

	gint col_idx = gda_data_model_get_column_index (model, name);
	if (col_idx == -1)
		return FALSE;

	GError *error = NULL;
	gboolean rv = gda_data_model_set_value_at (model, col_idx, self->dbpriv->row, (const GValue *) value, &error);


	return rv;
}

void
_midgard_dbobject_set_from_data_model (MidgardDBObject *self, GdaDataModel *model, gint row, gint start_field)
{
	g_return_if_fail (self != NULL);	
	g_return_if_fail (model != NULL);
	g_return_if_fail (row > -1);

	GError *error = NULL;

	/* Set user defined properties */
	guint n_props;
	guint i;
	GParamSpec **pspecs = g_object_class_list_properties (G_OBJECT_GET_CLASS (self), &n_props);
	if (!pspecs)
		return;

	const GValue *pval;
	for (i = 1; i < n_props; i++) {

		if (!(pspecs[i]->flags & G_PARAM_WRITABLE)) {
			g_print ("Ignoring read only property %s \n", pspecs[i]->name);
			continue;
		}

		const gchar *pname = pspecs[i]->name;
		gint col_idx = gda_data_model_get_column_index (model, pname);
		if (col_idx == -1)
			continue;
		
		pval = gda_data_model_get_value_at (model, col_idx, row, &error);
		if (!pval) {
			g_warning ("Failed to get '%s' property value: %s", pname, 
					error && error->message ? error->message : "Unknown reason");
			continue;
		}
		/* Overwrite NULL values */
		if (G_VALUE_TYPE (pval) == GDA_TYPE_NULL && pspecs[i]->value_type == G_TYPE_STRING)
			g_object_set (G_OBJECT (self), pname, "", NULL);
		else
			g_object_set_property (G_OBJECT (self), pname, pval);
	}

	/* Set metadata */
	MidgardDBObject *dbobject = MIDGARD_DBOBJECT (self);
	MidgardMetadata *metadata = MGD_DBOBJECT_METADATA (dbobject);
	if (metadata)
		MIDGARD_DBOBJECT_GET_CLASS (MIDGARD_DBOBJECT (metadata))->dbpriv->set_from_data_model (
				MIDGARD_DBOBJECT (metadata), model, row, start_field);

	return;
}

static void
__statement_insert_add_metadata_fields (MidgardDBObjectClass *klass, GString *colnames, GString *values)
{
	MidgardMetadataClass *mklass = MGD_DBCLASS_METADATA_CLASS (klass);
	if (!mklass)
		return;

	guint i;
	guint n_prop;
	GParamSpec **pspecs = g_object_class_list_properties (G_OBJECT_CLASS (mklass), &n_prop);

	if (!pspecs)
		return;

	for (i = 0; i < n_prop; i++) {
		const gchar *col_name = midgard_core_class_get_property_colname (MIDGARD_DBOBJECT_CLASS (mklass), pspecs[i]->name);
		if (!col_name)
			continue;
		g_string_append (colnames, ", ");
		g_string_append (values, ", ");
		g_string_append (colnames, col_name);
		const gchar *type_name = g_type_name (pspecs[i]->value_type);
		if (pspecs[i]->value_type == MIDGARD_TYPE_TIMESTAMP)
			type_name = "string";
		g_string_append_printf (values, "##%s::%s", col_name, type_name);
	}

	g_free (pspecs);
}

static void
__initialize_statement_insert (MidgardDBObjectClass *klass)
{
	GString *sql = g_string_new ("INSERT INTO ");
	guint n_props;
	guint i;
	const gchar *table = MGD_DBCLASS_TABLENAME (klass);
	g_return_if_fail (table != NULL);

	g_string_append (sql, table); 

	GParamSpec **pspecs = midgard_core_dbobject_class_list_properties (klass, &n_props);
	g_return_if_fail (pspecs != NULL);

	GString *colnames = g_string_new ("");
	GString *values = g_string_new ("");
	const gchar *pk = MGD_DBCLASS_PRIMARY (klass);
	gboolean add_coma = FALSE;

	for (i = 0; i < n_props; i++) {
		/* Ignore primary key */
		if (pk && g_str_equal (pspecs[i]->name, pk))
			continue;

		const gchar *col_name = midgard_core_class_get_property_colname (klass, pspecs[i]->name);
		if (add_coma) {
			g_string_append (colnames, ", ");
			g_string_append (values, ", ");
		}

		g_string_append (colnames, col_name);

		const gchar *type_name = g_type_name (pspecs[i]->value_type);
		if (pspecs[i]->value_type == MIDGARD_TYPE_TIMESTAMP)
			type_name = "string";
		g_string_append_printf (values, "##%s::%s", col_name, type_name);

		add_coma = TRUE;
	}

	__statement_insert_add_metadata_fields (klass, colnames, values);

	g_string_append_printf (sql, " (%s) VALUES (%s)", colnames->str, values->str);		

	GdaSqlParser *parser = gda_sql_parser_new ();
	GdaStatement *stmt;
	GError *error = NULL;
	stmt = gda_sql_parser_parse_string (parser, sql->str, NULL, &error);

	g_string_free (sql, TRUE);
	g_string_free (colnames, TRUE);
	g_string_free (values, TRUE);

	if (!stmt) {

		g_error ("Couldn't create %s class prepared statement. %s", 
				G_OBJECT_CLASS_NAME (klass), error && error->message ? error->message : "Unknown reason");
		return;
	}

	GdaSet *params; 
	if (!gda_statement_get_parameters (stmt, &params, &error)) {
		g_error ("Failed to create GdaSet for %s class. %s", 
				G_OBJECT_CLASS_NAME (klass), error && error->message ? error->message : "Unknown reason");
	}
	
	klass->dbpriv->statement_insert = stmt;
	klass->dbpriv->param_set_insert = params;
	
	return;
}

static void
__initialize_statement_update (MidgardDBObjectClass *klass)
{
	GString *sql = g_string_new ("UPDATE ");
	guint n_props;
	guint i;
	const gchar *table = MGD_DBCLASS_TABLENAME (klass);
	g_return_if_fail (table != NULL);

	g_string_append_printf (sql, "%s SET ", table); 

	GParamSpec **pspecs = midgard_core_dbobject_class_list_properties (klass, &n_props);
	g_return_if_fail (pspecs != NULL);

	const gchar *pk = MGD_DBCLASS_PRIMARY (klass);
	gboolean add_coma = FALSE;
	const gchar *col_name;
	const gchar *type_name;

	for (i = 0; i < n_props; i++) {
		/* Ignore primary key */
		if (pk && g_str_equal (pspecs[i]->name, pk))
			continue;

		col_name = midgard_core_class_get_property_colname (klass, pspecs[i]->name);
		type_name = g_type_name (pspecs[i]->value_type);
		if (pspecs[i]->value_type == MIDGARD_TYPE_TIMESTAMP)
			type_name = "string";
		g_string_append_printf (sql, "%s%s=##%s::%s", add_coma ? "," : "", col_name, col_name, type_name);

		add_coma = TRUE;
	}

	GParamSpec *pspec = g_object_class_find_property (G_OBJECT_CLASS (klass), pk);
	col_name = midgard_core_class_get_property_colname (klass, pk);
	type_name = g_type_name (pspec->value_type);
	g_string_append_printf (sql, " WHERE %s=#%s::%s", col_name, col_name, type_name);

	GdaSqlParser *parser = gda_sql_parser_new ();
	GdaStatement *stmt;
	GError *error = NULL;
	stmt = gda_sql_parser_parse_string (parser, sql->str, NULL, &error);

	g_string_free (sql, TRUE);

	if (!stmt) {

		g_error ("Couldn't create %s class prepared statement. %s", 
				G_OBJECT_CLASS_NAME (klass), error && error->message ? error->message : "Unknown reason");
		return;
	}

	GdaSet *params; 
	if (!gda_statement_get_parameters (stmt, &params, &error)) {
		g_error ("Failed to create GdaSet for %s class. %s", 
				G_OBJECT_CLASS_NAME (klass), error && error->message ? error->message : "Unknown reason");
	}
	
	klass->dbpriv->statement_update = stmt;
	klass->dbpriv->param_set_update = params;
	
	return;
}

GParamSpec**
midgard_core_dbobject_class_list_properties (MidgardDBObjectClass *klass, guint *n_props)
{
	g_return_val_if_fail (klass != NULL, NULL);

	MgdSchemaTypeAttr *type_attr = klass->dbpriv->storage_data;
	if (type_attr->params) {
		*n_props = g_slist_length (type_attr->_properties_list);
		return type_attr->params;
	}

	GSList *l;
	guint i = 0;
	guint n_params = g_slist_length (type_attr->_properties_list);
	type_attr->params = g_new (GParamSpec *, n_params);

	for (l = type_attr->_properties_list; l != NULL; l = l->next, i++) {
		type_attr->params[i] = g_object_class_find_property (G_OBJECT_CLASS (klass), (const gchar *) l->data);	
	}

	*n_props = n_params;
	return type_attr->params;
}

void 
midgard_core_dbobject_class_set_full_select (MidgardDBObjectClass *dbklass)
{
	g_return_if_fail (dbklass != NULL);

	MgdSchemaTypeAttr *type_attr = MIDGARD_DBOBJECT_CLASS (dbklass)->dbpriv->storage_data;

	type_attr->params = midgard_core_dbobject_class_list_properties (MIDGARD_DBOBJECT_CLASS (dbklass), &type_attr->num_properties);
	guint i;
	const gchar *field_name;
	GString *sql_full = g_string_new ("");
	
	for (i = 0; i < type_attr->num_properties; i++) {
		field_name = midgard_core_class_get_property_colname (MIDGARD_DBOBJECT_CLASS (dbklass), type_attr->params[i]->name);
		if (i > 0)
			g_string_append (sql_full, ", ");
		g_string_append_printf (sql_full, "%s AS %s", field_name, type_attr->params[i]->name);
	}

	type_attr->sql_select_full = g_strdup (sql_full->str);
	g_string_free (sql_full, TRUE);

	return;
}

static GParamSpec **
__list_properties (MidgardDBObjectClass *dbklass, guint *n_props)
{
	g_return_val_if_fail (dbklass != NULL, NULL);

	MgdSchemaTypeAttr *type_attr = dbklass->dbpriv->storage_data;
	if (type_attr->params) {
		*n_props = g_slist_length (type_attr->_properties_list);
		return type_attr->params;
	}

	GSList *l;
	guint i = 0;
	guint n_params = g_slist_length (type_attr->_properties_list);
	type_attr->params = g_new (GParamSpec *, n_params);

	for (l = type_attr->_properties_list; l != NULL; l = l->next, i++) {
		type_attr->params[i] = g_object_class_find_property (G_OBJECT_CLASS (dbklass), (const gchar *) l->data);	
	}

	*n_props = n_params;
	return type_attr->params;

}

static GParamSpec **
__list_storage_columns (MidgardDBObjectClass *dbklass, guint *n_cols)
{
	g_return_val_if_fail (dbklass != NULL, NULL);

	MgdSchemaTypeAttr *type_attr = dbklass->dbpriv->storage_data;
	if (type_attr->storage_params) {
		*n_cols = type_attr->storage_params_count;
		return type_attr->storage_params;
	}

	GSList *l;
	guint i = 0;

	/* Compute GParamSpec array size */
	for (l = type_attr->_properties_list; l != NULL; l = l->next) {
		if (midgard_core_class_get_property_colname (dbklass, (const gchar *)l->data))
			i++;
	}

	GParamSpec **pspecs = g_new (GParamSpec *, i); 

	i = 0;
	l = NULL;
	const gchar *colname;
	const gchar *property;
	GParamSpec *spec;

	for (l = type_attr->_properties_list; l != NULL; l = l->next) {
		property = (const gchar *) l->data;
		colname = midgard_core_class_get_property_colname (dbklass, property);
		if (!colname)
			continue;
		spec = g_object_class_find_property (G_OBJECT_CLASS (dbklass), property);
		pspecs[i]->name = (gchar *)colname;
		pspecs[i]->value_type = spec->value_type;
		i++;
	}

	type_attr->storage_params = pspecs;
	type_attr->storage_params_count = i;

	*n_cols = type_attr->storage_params_count;
	return type_attr->storage_params;
}

/* GOBJECT ROUTINES */

enum {
	PROPERTY_CONNECTION = 1
};

static void
__midgard_dbobject_instance_init (GTypeInstance *instance, gpointer g_class)
{
	MidgardDBObject *object = (MidgardDBObject *) instance;

	MIDGARD_DBOBJECT (object)->dbpriv = g_new(MidgardDBObjectPrivate, 1);
	MIDGARD_DBOBJECT (object)->dbpriv->mgd = NULL; /* read only */
	MIDGARD_DBOBJECT (object)->dbpriv->guid = NULL;
	MIDGARD_DBOBJECT (object)->dbpriv->datamodel = NULL;
	MIDGARD_DBOBJECT (object)->dbpriv->row = -1;	
	MIDGARD_DBOBJECT (object)->dbpriv->has_metadata = FALSE;
	MIDGARD_DBOBJECT (object)->dbpriv->metadata = NULL;
	MIDGARD_DBOBJECT (object)->dbpriv->is_in_storage = FALSE;

	MIDGARD_DBOBJECT (object)->dbpriv->storage_data =
		MIDGARD_DBOBJECT_GET_CLASS (object)->dbpriv->storage_data;

}

static GObject *
midgard_dbobject_constructor (GType type,
		guint n_construct_properties,
		GObjectConstructParam *construct_properties) 
{	
	GObject *object = (GObject *)
		G_OBJECT_CLASS (parent_class)->constructor (type,
				n_construct_properties,
				construct_properties);

	return G_OBJECT(object);
}

static void 
midgard_dbobject_dispose (GObject *object)
{
	MidgardDBObject *self = MIDGARD_DBOBJECT (object);
	if (self->dbpriv->datamodel && G_IS_OBJECT (self->dbpriv->datamodel))
		g_object_unref(self->dbpriv->datamodel);

	self->dbpriv->row = -1;

	/* Do not nullify metadata object, we might be in the middle of refcount decreasing */
	MidgardMetadata *metadata = MGD_DBOBJECT_METADATA (self);
	if (metadata && G_IS_OBJECT (metadata)) 
		g_object_unref (metadata);

	/* Drop reference to MidgardConnection */
	MidgardConnection *mgd = MIDGARD_DBOBJECT (self)->dbpriv->mgd;
	if (mgd != NULL && G_IS_OBJECT (mgd)) {	
		g_object_unref (MIDGARD_DBOBJECT (self)->dbpriv->mgd);
		MIDGARD_DBOBJECT (self)->dbpriv->mgd = NULL;
	}

	parent_class->dispose (object);
}

static void 
midgard_dbobject_finalize (GObject *object)
{
	MidgardDBObject *self = MIDGARD_DBOBJECT(object);

	if (!self)
		return;

	if (!self->dbpriv)
		return;

	g_free((gchar *)self->dbpriv->guid);
	self->dbpriv->guid = NULL;

	g_free(self->dbpriv);
	self->dbpriv = NULL;

	parent_class->finalize (object);
}

static const MidgardConnection *__get_connection(MidgardDBObject *self)
{
	g_assert(self != NULL);
	return self->dbpriv->mgd;
}

static void
__midgard_dbobject_get_property (GObject *object, guint property_id,
		GValue *value, GParamSpec *pspec)
{
	switch (property_id) {
		
		case PROPERTY_CONNECTION:			
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void
__midgard_dbobject_set_property (GObject *object, guint property_id,
		const GValue *value, GParamSpec *pspec)
{
	GObject *mgd;
	switch (property_id) {

		case PROPERTY_CONNECTION:
			if (!G_VALUE_HOLDS_OBJECT (value)) 
				return;

			if (!MIDGARD_IS_CONNECTION (g_value_get_object (value)))
				return;
	
			/* Add new reference to MidgardConnection object */
			MIDGARD_DBOBJECT (object)->dbpriv->mgd = g_value_dup_object (value);
			break;

  		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
			break;
	}
}

static void 
midgard_dbobject_class_init (MidgardDBObjectClass *klass, gpointer g_class_data)
{
	GObjectClass *object_class = G_OBJECT_CLASS (klass);
	parent_class = g_type_class_peek_parent (klass);
	
	object_class->constructor = midgard_dbobject_constructor;
	object_class->dispose = midgard_dbobject_dispose;
	object_class->finalize = midgard_dbobject_finalize;
	object_class->set_property = __midgard_dbobject_set_property;
	object_class->get_property = __midgard_dbobject_get_property;

	klass->get_connection = __get_connection;

	klass->dbpriv = g_new (MidgardDBObjectPrivate, 1);
	klass->dbpriv->storage_data = NULL;
	klass->dbpriv->create_storage = NULL;
	klass->dbpriv->update_storage = NULL;
	klass->dbpriv->storage_exists = NULL;
	klass->dbpriv->delete_storage = NULL;
	klass->dbpriv->add_fields_to_select_statement = _add_fields_to_select_statement;
	klass->dbpriv->get_property = _midgard_dbobject_get_property;
	klass->dbpriv->set_property = _midgard_dbobject_set_property;
	klass->dbpriv->set_from_data_model = _midgard_dbobject_set_from_data_model;
	klass->dbpriv->statement_insert = NULL;
	klass->dbpriv->set_statement_insert = __initialize_statement_insert;
	klass->dbpriv->statement_update = NULL;
	klass->dbpriv->set_statement_update = __initialize_statement_update;

	klass->dbpriv->list_properties = __list_properties;
	klass->dbpriv->list_storage_columns = __list_storage_columns;

	/* Properties */
	GParamSpec *pspec = g_param_spec_object ("connection",
			"",
			"",
			MIDGARD_TYPE_CONNECTION,
			G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);
	/**
	 * MidgardDBObject:connection:
	 * 
	 * Pointer to #MidgardConnection, given object has been initialized for
	 */  
	g_object_class_install_property (object_class, PROPERTY_CONNECTION, pspec);
}

/* Registers the type as a fundamental GType unless already registered. */ 
GType 
midgard_dbobject_get_type (void)
{
	static GType type = 0;
	if (type == 0) {
		static const GTypeInfo info = {
			sizeof (MidgardDBObjectClass),
			NULL,           /* base_init */
			NULL,           /* base_finalize */
			(GClassInitFunc) midgard_dbobject_class_init, 
			NULL,           /* class_finalize */
			NULL,           /* class_data */
			sizeof (MidgardDBObject),
			0,              /* n_preallocs */  
			__midgard_dbobject_instance_init
		};
		type = g_type_register_static (G_TYPE_OBJECT, "MidgardDBObject", &info, G_TYPE_FLAG_ABSTRACT);
	}
	return type;
}
