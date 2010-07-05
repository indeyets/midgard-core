/* midgard_key_config_file_context.c generated by valac, the Vala compiler
 * generated from midgard_key_config_file_context.vala, do not modify */

/* 
 * Copyright (C) 2009 Piotr Pokora <piotrek.pokora@gmail.com>
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

#include <glib.h>
#include <glib-object.h>
#include <stdlib.h>
#include <string.h>
#include <glib/gstdio.h>


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
#define _g_dir_close0(var) ((var == NULL) ? NULL : (var = (g_dir_close (var), NULL)))
#define _g_error_free0(var) ((var == NULL) ? NULL : (var = (g_error_free (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))
#define _g_regex_unref0(var) ((var == NULL) ? NULL : (var = (g_regex_unref (var), NULL)))

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

static gpointer midgard_key_config_file_context_parent_class = NULL;

GType midgard_key_config_context_get_type (void);
GType midgard_key_config_file_context_get_type (void);
enum  {
	MIDGARD_KEY_CONFIG_FILE_CONTEXT_DUMMY_PROPERTY
};
GQuark key_config_context_error_quark (void);
MidgardKeyConfigContext* midgard_key_config_context_construct (GType object_type, const char* context_path);
MidgardKeyConfigFileContext* midgard_key_config_file_context_new (const char* context_path, GError** error);
MidgardKeyConfigFileContext* midgard_key_config_file_context_construct (GType object_type, const char* context_path, GError** error);
static char** midgard_key_config_file_context_set_cfgs (MidgardKeyConfigFileContext* self, const char* path, gint i, int* result_length1);
static void _vala_array_add1 (char*** array, int* length, int* size, char* value);
#define MIDGARD_CONFIG_EXTENSION ".mcfg"
const char* midgard_key_config_context_get_context_path (MidgardKeyConfigContext* self);
static void _vala_array_add2 (char*** array, int* length, int* size, char* value);
static char** midgard_key_config_file_context_real_list_key_config (MidgardKeyConfigContext* base, int* result_length1);
static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func);
static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func);



MidgardKeyConfigFileContext* midgard_key_config_file_context_construct (GType object_type, const char* context_path, GError** error) {
	GError * _inner_error_;
	MidgardKeyConfigFileContext * self;
	g_return_val_if_fail (context_path != NULL, NULL);
	_inner_error_ = NULL;
	if (!g_path_is_absolute (context_path)) {
		_inner_error_ = g_error_new (KEY_CONFIG_CONTEXT_ERROR, KEY_CONFIG_CONTEXT_ERROR_PATH_IS_NOT_ABSOLUTE, "Expected absolute path. %s given", context_path);
		{
			if (_inner_error_->domain == KEY_CONFIG_CONTEXT_ERROR) {
				g_propagate_error (error, _inner_error_);
				g_object_unref (self);
				return NULL;
			} else {
				g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
				g_clear_error (&_inner_error_);
				return NULL;
			}
		}
	}
	self = (MidgardKeyConfigFileContext*) midgard_key_config_context_construct (object_type, context_path);
	return self;
}


MidgardKeyConfigFileContext* midgard_key_config_file_context_new (const char* context_path, GError** error) {
	return midgard_key_config_file_context_construct (MIDGARD_TYPE_KEY_CONFIG_FILE_CONTEXT, context_path, error);
}


static void _vala_array_add1 (char*** array, int* length, int* size, char* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (char*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static char* string_substring (const char* self, glong offset, glong len) {
	char* result = NULL;
	glong string_length;
	const char* start;
	g_return_val_if_fail (self != NULL, NULL);
	string_length = g_utf8_strlen (self, -1);
	if (offset < 0) {
		offset = string_length + offset;
		g_return_val_if_fail (offset >= 0, NULL);
	} else {
		g_return_val_if_fail (offset <= string_length, NULL);
	}
	if (len < 0) {
		len = string_length - offset;
	}
	g_return_val_if_fail ((offset + len) <= string_length, NULL);
	start = g_utf8_offset_to_pointer (self, offset);
	result = g_strndup (start, ((gchar*) g_utf8_offset_to_pointer (start, len)) - ((gchar*) start));
	return result;
}


static void _vala_array_add2 (char*** array, int* length, int* size, char* value) {
	if ((*length) == (*size)) {
		*size = (*size) ? (2 * (*size)) : 4;
		*array = g_renew (char*, *array, (*size) + 1);
	}
	(*array)[(*length)++] = value;
	(*array)[*length] = NULL;
}


static char** midgard_key_config_file_context_set_cfgs (MidgardKeyConfigFileContext* self, const char* path, gint i, int* result_length1) {
	char** result = NULL;
	GError * _inner_error_;
	GDir* dir;
	char* name;
	char** _tmp2_;
	gint _cfgs_size_;
	gint cfgs_length1;
	char** cfgs;
	char** _tmp9_;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (path != NULL, NULL);
	_inner_error_ = NULL;
	dir = NULL;
	{
		GDir* _tmp0_;
		GDir* _tmp1_;
		_tmp0_ = g_dir_open (path, 0, &_inner_error_);
		if (_inner_error_ != NULL) {
			if (_inner_error_->domain == G_FILE_ERROR) {
				goto __catch7_g_file_error;
			}
			_g_dir_close0 (dir);
			g_critical ("file %s: line %d: unexpected error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
			g_clear_error (&_inner_error_);
			return NULL;
		}
		dir = (_tmp1_ = _tmp0_, _g_dir_close0 (dir), _tmp1_);
	}
	goto __finally7;
	__catch7_g_file_error:
	{
		GError * e;
		e = _inner_error_;
		_inner_error_ = NULL;
		{
			g_warning ("midgard_key_config_file_context.vala:45: Can not open context path %s." \
" %s", path, e->message);
			_g_error_free0 (e);
		}
	}
	__finally7:
	if (_inner_error_ != NULL) {
		_g_dir_close0 (dir);
		g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
		g_clear_error (&_inner_error_);
		return NULL;
	}
	name = NULL;
	cfgs = (_tmp2_ = g_new0 (char*, 0 + 1), cfgs_length1 = 0, _cfgs_size_ = cfgs_length1, _tmp2_);
	while (TRUE) {
		char* _tmp3_;
		char* abspath;
		if (!((name = (_tmp3_ = g_strdup (g_dir_read_name (dir)), _g_free0 (name), _tmp3_)) != NULL)) {
			break;
		}
		abspath = g_build_filename (path, name, NULL);
		if (g_file_test (abspath, G_FILE_TEST_IS_DIR)) {
			char** _tmp5_;
			gint _children_size_;
			gint children_length1;
			gint _tmp4_;
			char** children;
			children = (_tmp5_ = midgard_key_config_file_context_set_cfgs (self, abspath, i, &_tmp4_), children_length1 = _tmp4_, _children_size_ = children_length1, _tmp5_);
			{
				char** child_collection;
				int child_collection_length1;
				int child_it;
				child_collection = children;
				child_collection_length1 = children_length1;
				for (child_it = 0; child_it < children_length1; child_it = child_it + 1) {
					const char* child;
					child = child_collection[child_it];
					{
						_vala_array_add1 (&cfgs, &cfgs_length1, &_cfgs_size_, g_strdup (child));
					}
				}
			}
			children = (_vala_array_free (children, children_length1, (GDestroyNotify) g_free), NULL);
		} else {
			if (g_str_has_suffix (abspath, MIDGARD_CONFIG_EXTENSION)) {
				char* path_wo_suffix;
				path_wo_suffix = string_substring (abspath, (glong) 0, g_utf8_strlen (abspath, -1) - g_utf8_strlen (MIDGARD_CONFIG_EXTENSION, -1));
				{
					char* _tmp6_;
					GRegex* _tmp7_;
					GRegex* regex;
					char* _tmp8_;
					regex = (_tmp7_ = g_regex_new (_tmp6_ = g_regex_escape_string (midgard_key_config_context_get_context_path ((MidgardKeyConfigContext*) self), -1), 0, 0, &_inner_error_), _g_free0 (_tmp6_), _tmp7_);
					if (_inner_error_ != NULL) {
						goto __catch8_g_error;
					}
					_tmp8_ = g_regex_replace_literal (regex, path_wo_suffix, (gssize) (-1), 0, "", 0, &_inner_error_);
					if (_inner_error_ != NULL) {
						_g_regex_unref0 (regex);
						goto __catch8_g_error;
					}
					_vala_array_add2 (&cfgs, &cfgs_length1, &_cfgs_size_, _tmp8_);
					_g_regex_unref0 (regex);
				}
				goto __finally8;
				__catch8_g_error:
				{
					g_clear_error (&_inner_error_);
					_inner_error_ = NULL;
					{
						g_warning ("midgard_key_config_file_context.vala:70: Weird path '%s', not added.", abspath);
					}
				}
				__finally8:
				if (_inner_error_ != NULL) {
					_g_free0 (path_wo_suffix);
					_g_free0 (abspath);
					_g_dir_close0 (dir);
					_g_free0 (name);
					cfgs = (_vala_array_free (cfgs, cfgs_length1, (GDestroyNotify) g_free), NULL);
					g_critical ("file %s: line %d: uncaught error: %s (%s, %d)", __FILE__, __LINE__, _inner_error_->message, g_quark_to_string (_inner_error_->domain), _inner_error_->code);
					g_clear_error (&_inner_error_);
					return NULL;
				}
				i++;
				_g_free0 (path_wo_suffix);
			}
		}
		_g_free0 (abspath);
	}
	result = (_tmp9_ = cfgs, *result_length1 = cfgs_length1, _tmp9_);
	_g_dir_close0 (dir);
	_g_free0 (name);
	return result;
	_g_dir_close0 (dir);
	_g_free0 (name);
	cfgs = (_vala_array_free (cfgs, cfgs_length1, (GDestroyNotify) g_free), NULL);
}


static char** midgard_key_config_file_context_real_list_key_config (MidgardKeyConfigContext* base, int* result_length1) {
	MidgardKeyConfigFileContext * self;
	char** result = NULL;
	gint _tmp0_;
	char** _tmp1_;
	self = (MidgardKeyConfigFileContext*) base;
	result = (_tmp1_ = midgard_key_config_file_context_set_cfgs (self, midgard_key_config_context_get_context_path ((MidgardKeyConfigContext*) self), 0, &_tmp0_), *result_length1 = _tmp0_, _tmp1_);
	return result;
}


static void midgard_key_config_file_context_class_init (MidgardKeyConfigFileContextClass * klass) {
	midgard_key_config_file_context_parent_class = g_type_class_peek_parent (klass);
	MIDGARD_KEY_CONFIG_CONTEXT_CLASS (klass)->list_key_config = midgard_key_config_file_context_real_list_key_config;
}


static void midgard_key_config_file_context_instance_init (MidgardKeyConfigFileContext * self) {
}


GType midgard_key_config_file_context_get_type (void) {
	static volatile gsize midgard_key_config_file_context_type_id__volatile = 0;
	if (g_once_init_enter (&midgard_key_config_file_context_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (MidgardKeyConfigFileContextClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) midgard_key_config_file_context_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (MidgardKeyConfigFileContext), 0, (GInstanceInitFunc) midgard_key_config_file_context_instance_init, NULL };
		GType midgard_key_config_file_context_type_id;
		midgard_key_config_file_context_type_id = g_type_register_static (MIDGARD_TYPE_KEY_CONFIG_CONTEXT, "MidgardKeyConfigFileContext", &g_define_type_info, 0);
		g_once_init_leave (&midgard_key_config_file_context_type_id__volatile, midgard_key_config_file_context_type_id);
	}
	return midgard_key_config_file_context_type_id__volatile;
}


static void _vala_array_destroy (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	if ((array != NULL) && (destroy_func != NULL)) {
		int i;
		for (i = 0; i < array_length; i = i + 1) {
			if (((gpointer*) array)[i] != NULL) {
				destroy_func (((gpointer*) array)[i]);
			}
		}
	}
}


static void _vala_array_free (gpointer array, gint array_length, GDestroyNotify destroy_func) {
	_vala_array_destroy (array, array_length, destroy_func);
	g_free (array);
}




