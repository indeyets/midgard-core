/* midgard_key_config_common.h generated by valac, the Vala compiler, do not modify */


#ifndef __SRC_MIDGARD_KEY_CONFIG_COMMON_H__
#define __SRC_MIDGARD_KEY_CONFIG_COMMON_H__

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>

G_BEGIN_DECLS


#define MIDGARD_TYPE_KEY_CONFIG_CONTEXT (midgard_key_config_context_get_type ())
#define MIDGARD_KEY_CONFIG_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContext))
#define MIDGARD_KEY_CONFIG_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContextClass))
#define MIDGARD_IS_KEY_CONFIG_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT))
#define MIDGARD_IS_KEY_CONFIG_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_KEY_CONFIG_CONTEXT))
#define MIDGARD_KEY_CONFIG_CONTEXT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_KEY_CONFIG_CONTEXT, MidgardKeyConfigContextClass))

typedef struct _MidgardKeyConfigContext MidgardKeyConfigContext;
typedef struct _MidgardKeyConfigContextClass MidgardKeyConfigContextClass;
typedef struct _MidgardKeyConfigContextPrivate MidgardKeyConfigContextPrivate;

#define MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT (midgard_key_config_file_context_get_type ())
#define MIDGARD_KEY_CONFIG_FILE_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT, MidgardKeyConfigFileContext))
#define MIDGARD_KEY_CONFIG_FILE_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT, MidgardKeyConfigFileContextClass))
#define MIDGARD_IS_KEY_CONFIG_FILE_CONTEXT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT))
#define MIDGARD_IS_KEY_CONFIG_FILE_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT))
#define MIDGARD_KEY_CONFIG_FILE_CONTEXT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT, MidgardKeyConfigFileContextClass))

typedef struct _MidgardKeyConfigFileContext MidgardKeyConfigFileContext;
typedef struct _MidgardKeyConfigFileContextClass MidgardKeyConfigFileContextClass;
typedef struct _MidgardKeyConfigFileContextPrivate MidgardKeyConfigFileContextPrivate;

#define MIDGARD_TYPE_KEY_CONFIG (midgard_key_config_get_type ())
#define MIDGARD_KEY_CONFIG(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIDGARD_TYPE_KEY_CONFIG, MidgardKeyConfig))
#define MIDGARD_KEY_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_KEY_CONFIG, MidgardKeyConfigClass))
#define MIDGARD_IS_KEY_CONFIG(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MIDGARD_TYPE_KEY_CONFIG))
#define MIDGARD_IS_KEY_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_KEY_CONFIG))
#define MIDGARD_KEY_CONFIG_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_KEY_CONFIG, MidgardKeyConfigClass))

typedef struct _MidgardKeyConfig MidgardKeyConfig;
typedef struct _MidgardKeyConfigClass MidgardKeyConfigClass;
typedef struct _MidgardKeyConfigPrivate MidgardKeyConfigPrivate;

#define MIDGARD_TYPE_KEY_CONFIG_FILE (midgard_key_config_file_get_type ())
#define MIDGARD_KEY_CONFIG_FILE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE, MidgardKeyConfigFile))
#define MIDGARD_KEY_CONFIG_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), MIDGARD_TYPE_KEY_CONFIG_FILE, MidgardKeyConfigFileClass))
#define MIDGARD_IS_KEY_CONFIG_FILE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE))
#define MIDGARD_IS_KEY_CONFIG_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), MIDGARD_TYPE_KEY_CONFIG_FILE))
#define MIDGARD_KEY_CONFIG_FILE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), MIDGARD_TYPE_KEY_CONFIG_FILE, MidgardKeyConfigFileClass))

typedef struct _MidgardKeyConfigFile MidgardKeyConfigFile;
typedef struct _MidgardKeyConfigFileClass MidgardKeyConfigFileClass;
typedef struct _MidgardKeyConfigFilePrivate MidgardKeyConfigFilePrivate;

struct _MidgardKeyConfigContext {
	GObject parent_instance;
	MidgardKeyConfigContextPrivate * priv;
};

struct _MidgardKeyConfigContextClass {
	GObjectClass parent_class;
	char** (*list_key_config) (MidgardKeyConfigContext* self, int* result_length1);
};

struct _MidgardKeyConfigFileContext {
	MidgardKeyConfigContext parent_instance;
	MidgardKeyConfigFileContextPrivate * priv;
};

struct _MidgardKeyConfigFileContextClass {
	MidgardKeyConfigContextClass parent_class;
};

typedef enum  {
	KEY_CONFIG_CONTEXT_ERROR_PATH_IS_NOT_ABSOLUTE
} KeyConfigContextError;
#define KEY_CONFIG_CONTEXT_ERROR key_config_context_error_quark ()
struct _MidgardKeyConfig {
	GObject parent_instance;
	MidgardKeyConfigPrivate * priv;
	char* path;
	MidgardKeyConfigContext* context;
};

struct _MidgardKeyConfigClass {
	GObjectClass parent_class;
	void (*set_value) (MidgardKeyConfig* self, const char* group, const char* key, const char* value);
	char* (*get_value) (MidgardKeyConfig* self, const char* group, const char* key);
	void (*set_comment) (MidgardKeyConfig* self, const char* group, const char* key, const char* comment);
	char* (*get_comment) (MidgardKeyConfig* self, const char* group, const char* key);
	char** (*list_groups) (MidgardKeyConfig* self, int* result_length1);
	gboolean (*group_exists) (MidgardKeyConfig* self, const char* name);
	gboolean (*delete_group) (MidgardKeyConfig* self, const char* name);
	gboolean (*store) (MidgardKeyConfig* self);
	gboolean (*load_from_data) (MidgardKeyConfig* self, const char* data);
	char* (*to_data) (MidgardKeyConfig* self);
};

struct _MidgardKeyConfigFile {
	MidgardKeyConfig parent_instance;
	MidgardKeyConfigFilePrivate * priv;
};

struct _MidgardKeyConfigFileClass {
	MidgardKeyConfigClass parent_class;
};


GType midgard_key_config_context_get_type (void);
MidgardKeyConfigContext* midgard_key_config_context_construct (GType object_type, const char* context_path);
char** midgard_key_config_context_list_key_config (MidgardKeyConfigContext* self, int* result_length1);
const char* midgard_key_config_context_get_context_path (MidgardKeyConfigContext* self);
GType midgard_key_config_file_context_get_type (void);
GQuark key_config_context_error_quark (void);
MidgardKeyConfigFileContext* midgard_key_config_file_context_new (const char* context_path, GError** error);
MidgardKeyConfigFileContext* midgard_key_config_file_context_construct (GType object_type, const char* context_path, GError** error);
GType midgard_key_config_get_type (void);
GType midgard_key_config_file_get_type (void);
MidgardKeyConfigFile* midgard_key_config_file_new (MidgardKeyConfigFileContext* keyctx, const char* path, GError** error);
MidgardKeyConfigFile* midgard_key_config_file_construct (GType object_type, MidgardKeyConfigFileContext* keyctx, const char* path, GError** error);
MidgardKeyConfig* midgard_key_config_construct (GType object_type, MidgardKeyConfigContext* keyctx, const char* path);
void midgard_key_config_set_value (MidgardKeyConfig* self, const char* group, const char* key, const char* value);
char* midgard_key_config_get_value (MidgardKeyConfig* self, const char* group, const char* key);
void midgard_key_config_set_comment (MidgardKeyConfig* self, const char* group, const char* key, const char* comment);
char* midgard_key_config_get_comment (MidgardKeyConfig* self, const char* group, const char* key);
char** midgard_key_config_list_groups (MidgardKeyConfig* self, int* result_length1);
gboolean midgard_key_config_group_exists (MidgardKeyConfig* self, const char* name);
gboolean midgard_key_config_delete_group (MidgardKeyConfig* self, const char* name);
gboolean midgard_key_config_store (MidgardKeyConfig* self);
gboolean midgard_key_config_load_from_data (MidgardKeyConfig* self, const char* data);
char* midgard_key_config_to_data (MidgardKeyConfig* self);


G_END_DECLS

#endif