
#include "nuitka/prelude.h"
#include "structseq.h"

// Sentinel PyObject to be used for all our call iterator endings. It will
// become a PyCObject pointing to NULL. It's address is unique, and that's
// enough for us to use it as sentinel value.
PyObject *_sentinel_value = NULL;

PyObject *Nuitka_dunder_compiled_value = NULL;

// We need to make sure this is local to the package, or else it will
// be taken from any external linkage.
#if defined(_NUITKA_MODULE) && !defined(_NUITKA_CONSTANTS_FROM_RESOURCE) && !defined(__cplusplus)
const unsigned char constant_bin[0];
#endif

PyObject *const_int_0;
PyObject *const_str_dot;
PyObject *const_float_0_0;
PyObject *const_float_1_0;
PyObject *const_int_neg_1;
PyObject *const_int_pos_1;
PyObject *const_int_pos_2;
PyObject *const_int_pos_3;
PyObject *const_int_pos_4;
PyObject *const_str_empty;
PyObject *const_str_space;
PyObject *const_dict_empty;
PyObject *const_bytes_empty;
PyObject *const_str_plain_i;
PyObject *const_str_plain_w;
PyObject *const_tuple_empty;
PyObject *const_str_plain_os;
PyObject *const_str_plain_rb;
PyObject *const_str_plain_re;
PyObject *const_str_plain_cls;
PyObject *const_str_plain_day;
PyObject *const_str_plain_end;
PyObject *const_str_plain_get;
PyObject *const_str_plain_int;
PyObject *const_str_plain_key;
PyObject *const_str_plain_len;
PyObject *const_str_plain_now;
PyObject *const_str_plain_sum;
PyObject *const_str_plain_Task;
PyObject *const_str_plain_args;
PyObject *const_str_plain_dict;
PyObject *const_str_plain_file;
PyObject *const_str_plain_hour;
PyObject *const_str_plain_iter;
PyObject *const_str_plain_join;
PyObject *const_str_plain_keys;
PyObject *const_str_plain_link;
PyObject *const_str_plain_name;
PyObject *const_str_plain_open;
PyObject *const_str_plain_path;
PyObject *const_str_plain_read;
PyObject *const_str_plain_repr;
PyObject *const_str_plain_self;
PyObject *const_str_plain_send;
PyObject *const_str_plain_site;
PyObject *const_str_plain_task;
PyObject *const_str_plain_time;
PyObject *const_str_plain_type;
PyObject *const_float_minus_0_0;
PyObject *const_float_minus_1_0;
PyObject *const_str_plain_bytes;
PyObject *const_str_plain_close;
PyObject *const_str_plain_items;
PyObject *const_str_plain_level;
PyObject *const_str_plain_match;
PyObject *const_str_plain_print;
PyObject *const_str_plain_range;
PyObject *const_str_plain_split;
PyObject *const_str_plain_throw;
PyObject *const_str_plain_tuple;
PyObject *const_str_plain_types;
PyObject *const_str_plain_Friday;
PyObject *const_str_plain_Monday;
PyObject *const_str_plain_Sunday;
PyObject *const_str_plain_append;
PyObject *const_str_plain_format;
PyObject *const_str_plain_kwargs;
PyObject *const_str_plain_locals;
PyObject *const_str_plain_minute;
PyObject *const_str_plain_origin;
PyObject *const_str_plain_remove;
PyObject *const_str_plain_search;
PyObject *const_str_plain_Trigger;
PyObject *const_str_plain_Tuesday;
PyObject *const_str_plain___all__;
PyObject *const_str_plain___cmp__;
PyObject *const_str_plain___doc__;
PyObject *const_str_plain_compile;
PyObject *const_str_plain_getattr;
PyObject *const_str_plain_globals;
PyObject *const_str_plain_inspect;
PyObject *const_str_plain_replace;
PyObject *const_str_plain_trigger;
PyObject *const_str_plain_FullTask;
PyObject *const_str_plain_Saturday;
PyObject *const_str_plain_Thursday;
PyObject *const_str_plain___dict__;
PyObject *const_str_plain___exit__;
PyObject *const_str_plain___file__;
PyObject *const_str_plain___init__;
PyObject *const_str_plain___iter__;
PyObject *const_str_plain___main__;
PyObject *const_str_plain___name__;
PyObject *const_str_plain___path__;
PyObject *const_str_plain___spec__;
PyObject *const_str_plain_add_task;
PyObject *const_str_plain_datetime;
PyObject *const_str_plain_filename;
PyObject *const_str_plain_fromlist;
PyObject *const_str_plain_fullTask;
PyObject *const_str_plain_run_task;
PyObject *const_str_plain_triggers;
PyObject *const_str_angle_metaclass;
PyObject *const_str_plain_Wednesday;
PyObject *const_str_plain___class__;
PyObject *const_str_plain___enter__;
PyObject *const_str_plain_all_tasks;
PyObject *const_str_plain_bytearray;
PyObject *const_str_plain_metaclass;
PyObject *const_tuple_str_dot_tuple;
PyObject *const_str_plain___cached__;
PyObject *const_str_plain___import__;
PyObject *const_str_plain___loader__;
PyObject *const_str_plain___module__;
PyObject *const_str_plain_createTask;
PyObject *const_str_plain___getitem__;
PyObject *const_str_plain___package__;
PyObject *const_str_plain___prepare__;
PyObject *const_str_plain__virtualenv;
PyObject *const_str_plain_classmethod;
PyObject *const_str_plain_create_file;
PyObject *const_str_plain_day_of_week;
PyObject *const_str_plain_delete_task;
PyObject *const_str_plain___builtins__;
PyObject *const_str_plain___compiled__;
PyObject *const_str_plain___qualname__;
PyObject *const_str_plain_create_tasks;
PyObject *const_str_plain_has_location;
PyObject *const_str_plain_staticmethod;
PyObject *const_str_plain___metaclass__;
PyObject *const_str_plain__initializing;
PyObject *const_str_plain_get_all_tasks;
PyObject *const_str_plain_link_validate;
PyObject *const_str_plain_schedule_cron;
PyObject *const_str_plain___orig_bases__;
PyObject *const_str_plain___mro_entries__;
PyObject *const_str_plain_delete_full_task;
PyObject *const_str_plain_get_next_trigger;
PyObject *const_tuple_none_none_none_tuple;
PyObject *const_tuple_str_plain_self_tuple;
PyObject *const_str_plain___class_getitem__;
PyObject *const_str_plain_validate_filename;
PyObject *const_str_plain_get_all_full_tasks;
PyObject *const_tuple_str_plain___class___tuple;
PyObject *const_str_plain_submodule_search_locations;
PyObject *const_tuple_str_plain_cls_str_plain_name_tuple;
PyObject *const_str_digest_25731c733fd74e8333aa29126ce85686;
PyObject *const_str_digest_45e4dde2057b0bf276d6a84f4c917d27;
PyObject *const_str_digest_75fd71b1edada749c2ef7ac810062295;
PyObject *const_str_digest_9816e8d1552296af90d250823c964059;
PyObject *const_str_digest_a20eaf14a08317a9c222b07bb65dfb6e;
PyObject *const_str_digest_adc474dd61fbd736d69c1bac5d9712e0;
PyObject *const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf;
PyObject *const_str_digest_fdd1f239b4f3ffd6efcccf00e4a637e0;
PyObject *const_tuple_anon_function_anon_builtin_function_or_method_tuple;

static void _createGlobalConstants(void) {
    NUITKA_MAY_BE_UNUSED PyObject *exception_type, *exception_value;
    NUITKA_MAY_BE_UNUSED PyTracebackObject *exception_tb;

#ifdef _MSC_VER
    // Prevent unused warnings in case of simple programs, the attribute
    // NUITKA_MAY_BE_UNUSED doesn't work for MSVC.
    (void *)exception_type; (void *)exception_value; (void *)exception_tb;
#endif

    const_int_0 = PyLong_FromUnsignedLong(0ul);
    const_str_dot = UNSTREAM_STRING_ASCII(&constant_bin[ 2241 ], 1, 0);
    const_float_0_0 = UNSTREAM_FLOAT(&constant_bin[ 6984 ]);
    const_float_1_0 = UNSTREAM_FLOAT(&constant_bin[ 6992 ]);
    const_int_neg_1 = PyLong_FromLong(-1l);
    const_int_pos_1 = PyLong_FromUnsignedLong(1ul);
    const_int_pos_2 = PyLong_FromUnsignedLong(2ul);
    const_int_pos_3 = PyLong_FromUnsignedLong(3ul);
    const_int_pos_4 = PyLong_FromUnsignedLong(4ul);
    const_str_empty = UNSTREAM_STRING_ASCII(&constant_bin[ 0 ], 0, 0);
    const_str_space = UNSTREAM_STRING_ASCII(&constant_bin[ 4 ], 1, 0);
    const_dict_empty = _PyDict_NewPresized( 0 );
    assert(PyDict_Size(const_dict_empty) == 0);
    const_bytes_empty = UNSTREAM_BYTES(&constant_bin[ 0 ], 0);
    const_str_plain_i = UNSTREAM_STRING_ASCII(&constant_bin[ 13 ], 1, 1);
    const_str_plain_w = UNSTREAM_STRING_ASCII(&constant_bin[ 1211 ], 1, 1);
    const_tuple_empty = PyTuple_New(0);
    const_str_plain_os = UNSTREAM_STRING_ASCII(&constant_bin[ 1314 ], 2, 1);
    const_str_plain_rb = UNSTREAM_STRING_ASCII(&constant_bin[ 7000 ], 2, 1);
    const_str_plain_re = UNSTREAM_STRING_ASCII(&constant_bin[ 1061 ], 2, 1);
    const_str_plain_cls = UNSTREAM_STRING_ASCII(&constant_bin[ 7002 ], 3, 1);
    const_str_plain_day = UNSTREAM_STRING_ASCII(&constant_bin[ 2009 ], 3, 1);
    const_str_plain_end = UNSTREAM_STRING_ASCII(&constant_bin[ 7005 ], 3, 1);
    const_str_plain_get = UNSTREAM_STRING_ASCII(&constant_bin[ 2301 ], 3, 1);
    const_str_plain_int = UNSTREAM_STRING_ASCII(&constant_bin[ 1010 ], 3, 1);
    const_str_plain_key = UNSTREAM_STRING_ASCII(&constant_bin[ 7008 ], 3, 1);
    const_str_plain_len = UNSTREAM_STRING_ASCII(&constant_bin[ 312 ], 3, 1);
    const_str_plain_now = UNSTREAM_STRING_ASCII(&constant_bin[ 7011 ], 3, 1);
    const_str_plain_sum = UNSTREAM_STRING_ASCII(&constant_bin[ 7014 ], 3, 1);
    const_str_plain_Task = UNSTREAM_STRING_ASCII(&constant_bin[ 259 ], 4, 1);
    const_str_plain_args = UNSTREAM_STRING_ASCII(&constant_bin[ 7017 ], 4, 1);
    const_str_plain_dict = UNSTREAM_STRING_ASCII(&constant_bin[ 876 ], 4, 1);
    const_str_plain_file = UNSTREAM_STRING_ASCII(&constant_bin[ 1631 ], 4, 1);
    const_str_plain_hour = UNSTREAM_STRING_ASCII(&constant_bin[ 7021 ], 4, 1);
    const_str_plain_iter = UNSTREAM_STRING_ASCII(&constant_bin[ 7025 ], 4, 1);
    const_str_plain_join = UNSTREAM_STRING_ASCII(&constant_bin[ 6046 ], 4, 1);
    const_str_plain_keys = UNSTREAM_STRING_ASCII(&constant_bin[ 7029 ], 4, 1);
    const_str_plain_link = UNSTREAM_STRING_ASCII(&constant_bin[ 2263 ], 4, 1);
    const_str_plain_name = UNSTREAM_STRING_ASCII(&constant_bin[ 0 ], 4, 1);
    const_str_plain_open = UNSTREAM_STRING_ASCII(&constant_bin[ 1851 ], 4, 1);
    const_str_plain_path = UNSTREAM_STRING_ASCII(&constant_bin[ 1917 ], 4, 1);
    const_str_plain_read = UNSTREAM_STRING_ASCII(&constant_bin[ 4101 ], 4, 1);
    const_str_plain_repr = UNSTREAM_STRING_ASCII(&constant_bin[ 6252 ], 4, 1);
    const_str_plain_self = UNSTREAM_STRING_ASCII(&constant_bin[ 7033 ], 4, 1);
    const_str_plain_send = UNSTREAM_STRING_ASCII(&constant_bin[ 7004 ], 4, 1);
    const_str_plain_site = UNSTREAM_STRING_ASCII(&constant_bin[ 7037 ], 4, 1);
    const_str_plain_task = UNSTREAM_STRING_ASCII(&constant_bin[ 2246 ], 4, 1);
    const_str_plain_time = UNSTREAM_STRING_ASCII(&constant_bin[ 850 ], 4, 1);
    const_str_plain_type = UNSTREAM_STRING_ASCII(&constant_bin[ 2644 ], 4, 1);
    const_float_minus_0_0 = UNSTREAM_FLOAT(&constant_bin[ 7041 ]);
    const_float_minus_1_0 = UNSTREAM_FLOAT(&constant_bin[ 7049 ]);
    const_str_plain_bytes = UNSTREAM_STRING_ASCII(&constant_bin[ 7057 ], 5, 1);
    const_str_plain_close = UNSTREAM_STRING_ASCII(&constant_bin[ 7062 ], 5, 1);
    const_str_plain_items = UNSTREAM_STRING_ASCII(&constant_bin[ 7067 ], 5, 1);
    const_str_plain_level = UNSTREAM_STRING_ASCII(&constant_bin[ 197 ], 5, 1);
    const_str_plain_match = UNSTREAM_STRING_ASCII(&constant_bin[ 7072 ], 5, 1);
    const_str_plain_print = UNSTREAM_STRING_ASCII(&constant_bin[ 7077 ], 5, 1);
    const_str_plain_range = UNSTREAM_STRING_ASCII(&constant_bin[ 285 ], 5, 1);
    const_str_plain_split = UNSTREAM_STRING_ASCII(&constant_bin[ 7082 ], 5, 1);
    const_str_plain_throw = UNSTREAM_STRING_ASCII(&constant_bin[ 7087 ], 5, 1);
    const_str_plain_tuple = UNSTREAM_STRING_ASCII(&constant_bin[ 7092 ], 5, 1);
    const_str_plain_types = UNSTREAM_STRING_ASCII(&constant_bin[ 7097 ], 5, 1);
    const_str_plain_Friday = UNSTREAM_STRING_ASCII(&constant_bin[ 7102 ], 6, 1);
    const_str_plain_Monday = UNSTREAM_STRING_ASCII(&constant_bin[ 7108 ], 6, 1);
    const_str_plain_Sunday = UNSTREAM_STRING_ASCII(&constant_bin[ 7114 ], 6, 1);
    const_str_plain_append = UNSTREAM_STRING_ASCII(&constant_bin[ 7120 ], 6, 1);
    const_str_plain_format = UNSTREAM_STRING_ASCII(&constant_bin[ 7126 ], 6, 1);
    const_str_plain_kwargs = UNSTREAM_STRING_ASCII(&constant_bin[ 7132 ], 6, 1);
    const_str_plain_locals = UNSTREAM_STRING_ASCII(&constant_bin[ 2894 ], 6, 1);
    const_str_plain_minute = UNSTREAM_STRING_ASCII(&constant_bin[ 7138 ], 6, 1);
    const_str_plain_origin = UNSTREAM_STRING_ASCII(&constant_bin[ 7144 ], 6, 1);
    const_str_plain_remove = UNSTREAM_STRING_ASCII(&constant_bin[ 7150 ], 6, 1);
    const_str_plain_search = UNSTREAM_STRING_ASCII(&constant_bin[ 7156 ], 6, 1);
    const_str_plain_Trigger = UNSTREAM_STRING_ASCII(&constant_bin[ 576 ], 7, 1);
    const_str_plain_Tuesday = UNSTREAM_STRING_ASCII(&constant_bin[ 7162 ], 7, 1);
    const_str_plain___all__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7169 ], 7, 1);
    const_str_plain___cmp__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7176 ], 7, 1);
    const_str_plain___doc__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7183 ], 7, 1);
    const_str_plain_compile = UNSTREAM_STRING_ASCII(&constant_bin[ 7190 ], 7, 1);
    const_str_plain_getattr = UNSTREAM_STRING_ASCII(&constant_bin[ 7197 ], 7, 1);
    const_str_plain_globals = UNSTREAM_STRING_ASCII(&constant_bin[ 7204 ], 7, 1);
    const_str_plain_inspect = UNSTREAM_STRING_ASCII(&constant_bin[ 7211 ], 7, 1);
    const_str_plain_replace = UNSTREAM_STRING_ASCII(&constant_bin[ 2749 ], 7, 1);
    const_str_plain_trigger = UNSTREAM_STRING_ASCII(&constant_bin[ 2429 ], 7, 1);
    const_str_plain_FullTask = UNSTREAM_STRING_ASCII(&constant_bin[ 255 ], 8, 1);
    const_str_plain_Saturday = UNSTREAM_STRING_ASCII(&constant_bin[ 7218 ], 8, 1);
    const_str_plain_Thursday = UNSTREAM_STRING_ASCII(&constant_bin[ 7226 ], 8, 1);
    const_str_plain___dict__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7234 ], 8, 1);
    const_str_plain___exit__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7242 ], 8, 1);
    const_str_plain___file__ = UNSTREAM_STRING_ASCII(&constant_bin[ 1629 ], 8, 1);
    const_str_plain___init__ = UNSTREAM_STRING_ASCII(&constant_bin[ 2363 ], 8, 1);
    const_str_plain___iter__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7250 ], 8, 1);
    const_str_plain___main__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7258 ], 8, 1);
    const_str_plain___name__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7266 ], 8, 1);
    const_str_plain___path__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7274 ], 8, 1);
    const_str_plain___spec__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7282 ], 8, 1);
    const_str_plain_add_task = UNSTREAM_STRING_ASCII(&constant_bin[ 6067 ], 8, 1);
    const_str_plain_datetime = UNSTREAM_STRING_ASCII(&constant_bin[ 846 ], 8, 1);
    const_str_plain_filename = UNSTREAM_STRING_ASCII(&constant_bin[ 6719 ], 8, 1);
    const_str_plain_fromlist = UNSTREAM_STRING_ASCII(&constant_bin[ 7290 ], 8, 1);
    const_str_plain_fullTask = UNSTREAM_STRING_ASCII(&constant_bin[ 6560 ], 8, 1);
    const_str_plain_run_task = UNSTREAM_STRING_ASCII(&constant_bin[ 6020 ], 8, 1);
    const_str_plain_triggers = UNSTREAM_STRING_ASCII(&constant_bin[ 3129 ], 8, 1);
    const_str_angle_metaclass = UNSTREAM_STRING_ASCII(&constant_bin[ 7298 ], 11, 0);
    const_str_plain_Wednesday = UNSTREAM_STRING_ASCII(&constant_bin[ 7309 ], 9, 1);
    const_str_plain___class__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7318 ], 9, 1);
    const_str_plain___enter__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7327 ], 9, 1);
    const_str_plain_all_tasks = UNSTREAM_STRING_ASCII(&constant_bin[ 6470 ], 9, 1);
    const_str_plain_bytearray = UNSTREAM_STRING_ASCII(&constant_bin[ 7336 ], 9, 1);
    const_str_plain_metaclass = UNSTREAM_STRING_ASCII(&constant_bin[ 7299 ], 9, 1);
    const_tuple_str_dot_tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(const_tuple_str_dot_tuple, 0, const_str_dot); Py_INCREF(const_str_dot);
    const_str_plain___cached__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7345 ], 10, 1);
    const_str_plain___import__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7355 ], 10, 1);
    const_str_plain___loader__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7365 ], 10, 1);
    const_str_plain___module__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7375 ], 10, 1);
    const_str_plain_createTask = UNSTREAM_STRING_ASCII(&constant_bin[ 6318 ], 10, 1);
    const_str_plain___getitem__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7385 ], 11, 1);
    const_str_plain___package__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7396 ], 11, 1);
    const_str_plain___prepare__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7407 ], 11, 1);
    const_str_plain__virtualenv = UNSTREAM_STRING_ASCII(&constant_bin[ 5276 ], 11, 1);
    const_str_plain_classmethod = UNSTREAM_STRING_ASCII(&constant_bin[ 1976 ], 11, 1);
    const_str_plain_create_file = UNSTREAM_STRING_ASCII(&constant_bin[ 6218 ], 11, 1);
    const_str_plain_day_of_week = UNSTREAM_STRING_ASCII(&constant_bin[ 7418 ], 11, 1);
    const_str_plain_delete_task = UNSTREAM_STRING_ASCII(&constant_bin[ 6450 ], 11, 1);
    const_str_plain___builtins__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7429 ], 12, 1);
    const_str_plain___compiled__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7441 ], 12, 1);
    const_str_plain___qualname__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7453 ], 12, 1);
    const_str_plain_create_tasks = UNSTREAM_STRING_ASCII(&constant_bin[ 6580 ], 12, 1);
    const_str_plain_has_location = UNSTREAM_STRING_ASCII(&constant_bin[ 7465 ], 12, 1);
    const_str_plain_staticmethod = UNSTREAM_STRING_ASCII(&constant_bin[ 1695 ], 12, 1);
    const_str_plain___metaclass__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7477 ], 13, 1);
    const_str_plain__initializing = UNSTREAM_STRING_ASCII(&constant_bin[ 7490 ], 13, 1);
    const_str_plain_get_all_tasks = UNSTREAM_STRING_ASCII(&constant_bin[ 6466 ], 13, 1);
    const_str_plain_link_validate = UNSTREAM_STRING_ASCII(&constant_bin[ 6907 ], 13, 1);
    const_str_plain_schedule_cron = UNSTREAM_STRING_ASCII(&constant_bin[ 6193 ], 13, 1);
    const_str_plain___orig_bases__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7503 ], 14, 1);
    const_str_plain___mro_entries__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7517 ], 15, 1);
    const_str_plain_delete_full_task = UNSTREAM_STRING_ASCII(&constant_bin[ 6871 ], 16, 1);
    const_str_plain_get_next_trigger = UNSTREAM_STRING_ASCII(&constant_bin[ 6507 ], 16, 1);
    const_tuple_none_none_none_tuple = PyTuple_New(3);
    PyTuple_SET_ITEM(const_tuple_none_none_none_tuple, 0, Py_None); Py_INCREF(Py_None);
    PyTuple_SET_ITEM(const_tuple_none_none_none_tuple, 1, Py_None); Py_INCREF(Py_None);
    PyTuple_SET_ITEM(const_tuple_none_none_none_tuple, 2, Py_None); Py_INCREF(Py_None);
    const_tuple_str_plain_self_tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(const_tuple_str_plain_self_tuple, 0, const_str_plain_self); Py_INCREF(const_str_plain_self);
    const_str_plain___class_getitem__ = UNSTREAM_STRING_ASCII(&constant_bin[ 7532 ], 17, 1);
    const_str_plain_validate_filename = UNSTREAM_STRING_ASCII(&constant_bin[ 6710 ], 17, 1);
    const_str_plain_get_all_full_tasks = UNSTREAM_STRING_ASCII(&constant_bin[ 6760 ], 18, 1);
    const_tuple_str_plain___class___tuple = PyTuple_New(1);
    PyTuple_SET_ITEM(const_tuple_str_plain___class___tuple, 0, const_str_plain___class__); Py_INCREF(const_str_plain___class__);
    const_str_plain_submodule_search_locations = UNSTREAM_STRING_ASCII(&constant_bin[ 7549 ], 26, 1);
    const_tuple_str_plain_cls_str_plain_name_tuple = PyTuple_New(2);
    PyTuple_SET_ITEM(const_tuple_str_plain_cls_str_plain_name_tuple, 0, const_str_plain_cls); Py_INCREF(const_str_plain_cls);
    PyTuple_SET_ITEM(const_tuple_str_plain_cls_str_plain_name_tuple, 1, const_str_plain_name); Py_INCREF(const_str_plain_name);
    const_str_digest_25731c733fd74e8333aa29126ce85686 = UNSTREAM_STRING_ASCII(&constant_bin[ 7575 ], 2, 0);
    const_str_digest_45e4dde2057b0bf276d6a84f4c917d27 = UNSTREAM_STRING_ASCII(&constant_bin[ 7577 ], 7, 0);
    const_str_digest_75fd71b1edada749c2ef7ac810062295 = UNSTREAM_STRING_ASCII(&constant_bin[ 7584 ], 46, 0);
    const_str_digest_9816e8d1552296af90d250823c964059 = UNSTREAM_STRING_ASCII(&constant_bin[ 7630 ], 46, 0);
    const_str_digest_a20eaf14a08317a9c222b07bb65dfb6e = UNSTREAM_STRING_ASCII(&constant_bin[ 7676 ], 69, 0);
    const_str_digest_adc474dd61fbd736d69c1bac5d9712e0 = UNSTREAM_STRING_ASCII(&constant_bin[ 7745 ], 47, 0);
    const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf = UNSTREAM_STRING_ASCII(&constant_bin[ 7792 ], 71, 0);
    const_str_digest_fdd1f239b4f3ffd6efcccf00e4a637e0 = UNSTREAM_STRING_ASCII(&constant_bin[ 7863 ], 48, 0);
    const_tuple_anon_function_anon_builtin_function_or_method_tuple = PyTuple_New(2);
    PyTuple_SET_ITEM(const_tuple_anon_function_anon_builtin_function_or_method_tuple, 0, (PyObject *)&PyFunction_Type); Py_INCREF((PyObject *)&PyFunction_Type);
    PyTuple_SET_ITEM(const_tuple_anon_function_anon_builtin_function_or_method_tuple, 1, (PyObject *)&PyCFunction_Type); Py_INCREF((PyObject *)&PyCFunction_Type);

#if _NUITKA_EXE
    /* Set the "sys.executable" path to the original CPython executable. */
    PySys_SetObject(
        (char *)"executable",
        const_str_digest_a20eaf14a08317a9c222b07bb65dfb6e
    );

#ifndef _NUITKA_STANDALONE
    /* Set the "sys.prefix" path to the original one. */
    PySys_SetObject(
        (char *)"prefix",
        const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf
    );

    /* Set the "sys.prefix" path to the original one. */
    PySys_SetObject(
        (char *)"exec_prefix",
        const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf
    );


#if PYTHON_VERSION >= 300
    /* Set the "sys.base_prefix" path to the original one. */
    PySys_SetObject(
        (char *)"base_prefix",
        const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf
    );

    /* Set the "sys.exec_base_prefix" path to the original one. */
    PySys_SetObject(
        (char *)"base_exec_prefix",
        const_str_digest_beebff5fbcf56d5fdefd99b7b8c16abf
    );

#endif
#endif
#endif

    static PyTypeObject Nuitka_VersionInfoType;

    // Same fields as "sys.version_info" except no serial number.
    static PyStructSequence_Field Nuitka_VersionInfoFields[] = {
        {(char *)"major", (char *)"Major release number"},
        {(char *)"minor", (char *)"Minor release number"},
        {(char *)"micro", (char *)"Micro release number"},
        {(char *)"releaselevel", (char *)"'alpha', 'beta', 'candidate', or 'release'"},
        {0}
    };

    static PyStructSequence_Desc Nuitka_VersionInfoDesc = {
        (char *)"__nuitka_version__",                                    /* name */
        (char *)"__compiled__\n\nVersion information as a named tuple.", /* doc */
        Nuitka_VersionInfoFields,                                        /* fields */
        4
    };

    PyStructSequence_InitType(&Nuitka_VersionInfoType, &Nuitka_VersionInfoDesc);

    Nuitka_dunder_compiled_value = PyStructSequence_New(&Nuitka_VersionInfoType);
    assert(Nuitka_dunder_compiled_value != NULL);

    PyStructSequence_SET_ITEM(Nuitka_dunder_compiled_value, 0, PyInt_FromLong(0));
    PyStructSequence_SET_ITEM(Nuitka_dunder_compiled_value, 1, PyInt_FromLong(6));
    PyStructSequence_SET_ITEM(Nuitka_dunder_compiled_value, 2, PyInt_FromLong(8));

    PyStructSequence_SET_ITEM(Nuitka_dunder_compiled_value, 3, Nuitka_String_FromString("release"));

    // Prevent users from creating the Nuitka version type object.
    Nuitka_VersionInfoType.tp_init = NULL;
    Nuitka_VersionInfoType.tp_new = NULL;


}

// In debug mode we can check that the constants were not tampered with in any
// given moment. We typically do it at program exit, but we can add extra calls
// for sanity.
#ifndef __NUITKA_NO_ASSERT__
void checkGlobalConstants(void) {

}
#endif

void createGlobalConstants(void) {
    if (_sentinel_value == NULL) {
#if PYTHON_VERSION < 300
        _sentinel_value = PyCObject_FromVoidPtr(NULL, NULL);
#else
        // The NULL value is not allowed for a capsule, so use something else.
        _sentinel_value = PyCapsule_New((void *)27, "sentinel", NULL);
#endif
        assert(_sentinel_value);

        _createGlobalConstants();
    }
}
