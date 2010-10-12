
const string MISS_IMPL = "MISSING IMPLEMENTATION ";
const string DEFAULT_CLASSNAME = "CRFoo";
const string DEFAULT_TABLENAME = "CRFoo_table";
const string TITLE_PROPERTY_NAME = "title_property";
const string TITLE_COLUMN = "title_col";
const string ABSTRACT_PROPERTY_NAME = "abstract_property";
const string ABSTRACT_COLUMN = "abstract_col";

void main (string[] args) {
	Test.init (ref args);
	midgardcr_test_add_config_tests ();
	midgardcr_test_add_sql_storage_manager_tests ();
	midgardcr_test_add_object_model_tests ();
	midgardcr_test_add_object_model_property_tests ();
	midgardcr_test_add_schema_builder_tests ();
	midgardcr_test_add_sql_storage_model_manager_tests ();
	Test.run ();
}
