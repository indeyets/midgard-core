using MidgardCR;

void midgardcr_test_add_sql_storage_model_manager_tests () {

	/* constructor */
	Test.add_func ("/SQLStorageModelManager/constructor", () => {
		MidgardCR.SQLStorageModelManager mm = new MidgardCR.SQLStorageModelManager ();
		assert (mm != null);	
	
		MidgardCR.SQLStorageManager storage_manager = null;
		MidgardCR.Config config = new MidgardCR.Config ();	

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			storage_manager = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (storage_manager != null);
		
		MidgardCR.StorageModelManager model_manager = storage_manager.model_manager;
		assert (model_manager != null);
		assert (model_manager is MidgardCR.SQLStorageModelManager);
	});

	Test.add_func ("/SQLStorageModelManager/prepare_create", () => {	
		MidgardCR.SQLStorageManager storage_manager = null;
		MidgardCR.Config config = new MidgardCR.Config ();	

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			storage_manager = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (storage_manager != null);
	
		bool opened = false;
                /* SUCCESS */
                try {
                        opened = storage_manager.open ();
                } catch (StorageManagerError e) {
                        GLib.warning (e.message);
                }
                assert (opened == true);
	
		MidgardCR.StorageModelManager model_manager = storage_manager.model_manager;
		assert (model_manager != null);
		assert (model_manager is MidgardCR.SQLStorageModelManager);

		MidgardCR.SchemaModel model = new MidgardCR.SchemaModel (DEFAULT_CLASSNAME);
                assert (model != null);
                assert (model.name == DEFAULT_CLASSNAME);

                /* SUCCESS */
                MidgardCR.SchemaModelProperty prop_model = new MidgardCR.SchemaModelProperty (DEFAULT_PROPERTY_NAME, "string", "");
                assert (prop_model != null);

                model.add_model (prop_model);

		/* Add Schema model to StorageModelManager */
		model_manager.add_model (model);
	
		/* SUCCESS */
		try {
			model_manager.prepare_create ();
		} catch (ValidationError e) {
			GLib.warning (e.message);
		}	
	});

	Test.add_func ("/SQLStorageModelManager/execute", () => {	
		MidgardCR.SQLStorageManager storage_manager = null;
		MidgardCR.Config config = new MidgardCR.Config ();	

		try {
			config.read_configuration (DEFAULT_CONFIGURATION, true);
		} catch (GLib.FileError e) {
			GLib.warning (e.message);
		} catch (GLib.KeyFileError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */		
		try {
			storage_manager = new MidgardCR.SQLStorageManager ("test_manager", config);
		} catch (StorageManagerError e) {
			GLib.warning ("Failed to initialize new SQLStorageManager");
		}
		assert (storage_manager != null);
	
		bool opened = false;
                /* SUCCESS */
                try {
                        opened = storage_manager.open ();
                } catch (StorageManagerError e) {
                        GLib.warning (e.message);
                }
                assert (opened == true);
	
		MidgardCR.StorageModelManager model_manager = storage_manager.model_manager;
		assert (model_manager != null);
		assert (model_manager is MidgardCR.SQLStorageModelManager);

		MidgardCR.SchemaModel model = new MidgardCR.SchemaModel (DEFAULT_CLASSNAME);
                assert (model != null);
                assert (model.name == DEFAULT_CLASSNAME);

                /* SUCCESS */
                MidgardCR.SchemaModelProperty prop_model = new MidgardCR.SchemaModelProperty (DEFAULT_PROPERTY_NAME, "string", "");
                assert (prop_model != null);

                model.add_model (prop_model);

		/* Add Schema model to StorageModelManager */
		model_manager.add_model (model);

		/* SUCCESS */
		try {
			model_manager.prepare_create ();
		} catch (ValidationError e) {
			GLib.warning (e.message);
		}

		/* SUCCESS */
		try {
			model_manager.execute ();
		} catch (ExecutableError e) {
			GLib.warning (e.message);
		}
	});
}
