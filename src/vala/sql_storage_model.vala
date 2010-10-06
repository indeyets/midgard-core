
namespace MidgardCR {

	/**
	 * SQLStorageModel describes relation between class and it's table in SQL database.
	 * It's name property holds the name of the class, and location holds the name of the table.
	 *
	 * Property and column name mapping is done with {@link SQLStorageModelProperty}. 
	 * 
	 * {@link SQLStorageModelManager} provides access to all available schema and SQL storage models.
	 * 
	 */ 
	public class SQLStorageModel: GLib.Object, Executable, StorageExecutor, Model, StorageModel {
		
		/* private properties */

		private Model[] _models = null;
		internal StorageManager _storage_manager = null;

		/* public properties */
		
		/** 
		 * SQL database' table name, to store data for objects of the class
		 * this model is initialized for.
		 */ 
		public string location { get; set;}

		/**
                 * Holds the name of the class, StorageModel is initialized for.
                 */
                public string name { get; set; }
                /**
                 * Holds the namespace of model's class
                 */
                public string @namespace { get; set; }
                /**
                 * Parent model of the model.
                 */
                public Model? parent { get; set; }
		/**
		 * Holds reference to {@link SQLStorageManager} object 
		 */
		public unowned StorageManager storagemanager { 	
			get { return this._storage_manager; }
		}			

		/**
		 * Constructor
		 * 
		 * Creates new SQLStorageModel object for given class name and location.
		 *
		 * Created SQLStorageModel object describes database table (location) for the class
		 * it is initialized for. For example, data of 'MyContacts' class objects should be 
		 * stored in table 'my_contacts_tbl'. In such case, 'MyContacts' should be classname, 
		 * and 'my_contacts_tbl' should be location.
		 * 
		 * @param classname name of the class 
		 * @param location table name
		 */
		public SQLStorageModel (string classname, string location) {
			Object (name: classname, location: location);
		}
	
		/**
		 * Add new property model 
		 *
		 * Any model added to SQLStorageModel one should be an instance
		 * of {@link SQLStorageModelProperty}. In any other case, model 
		 * will be marked as invalid, during validation process.  
		 *
		 * @param model {@link Model} to add
		 *
		 * @return {@link Model} instance (self reference)
		 */	
		public Model add_model (Model model) { 
			this._models += model;			
			model.parent = this;
			return this; 
		}

		/**
		 * Get {@link SQLStorageModelProperty} model by given name.
		 * 
		 * @param name {@link Model} name to look for
		 *
		 * @return {@link Model} if found, null otherwise
		 */
		public unowned Model? get_model_by_name (string name) { 
			if (this._models == null)
				return null; 

			foreach (unowned Model model in this._models) {
				if (model.name == name)
					return model;
			}
			
			return null;
		}

		/**
		 * List all associated models
		 *
		 * @return array of {@link Model} objects, or null if none associated
		 */
		public unowned Model[]? list_models () { 
			return this._models; 
		}
		
		/**
		 * Check whether model is valid
		 *
		 * Conditions to mark model as invalid:
		 * * models with duplicated names
		 * * empty models
		 *
		 */
 		public void is_valid () throws ValidationError { 
			if (this._models == null)
				throw new MidgardCR.ValidationError.REFERENCE_INVALID ("No property models associated.");

			/* TODO */
			/* Check if name does not containt invalid characters */

			string[] names = new string[0];
			foreach (MidgardCR.Model model in this._models) {
				/* TODO, check if it's SchemaModel or StorageModel */	
				foreach (string name in names) {
					if (name == model.name)
						throw new MidgardCR.ValidationError.NAME_DUPLICATED ("Duplicated model name found");
				}
				names += model.name;
			}	
		}					

		/* StorageExecutor methods */
		public bool exists () {
			return false;
		} 
		
                public void prepare_create () throws ValidationError {

		}

                public void prepare_update () throws ValidationError {

		}

                public void prepare_save () throws ValidationError {

		}

                public void prepare_remove () throws ValidationError {

		}

                public void prepare_purge () throws ValidationError {

		}

		/* Executable methods */
		public void execute () { 
			return; 
		}		
	}
}