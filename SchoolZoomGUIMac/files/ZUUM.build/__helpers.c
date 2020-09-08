// This file contains helper functions that are automatically created from
// templates.

#include "nuitka/prelude.h"

extern PyObject *callPythonFunction( PyObject *func, PyObject **args, int count );


PyObject *CALL_FUNCTION_WITH_ARGS1(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 1; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 1 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 1; i++) {
                Py_INCREF(args[i]);
            }

            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 1 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 1 * sizeof(PyObject *));
            memcpy(python_pars + 1, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (parseArgumentsPos(function, python_pars, args, 1)) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 1 + 1 == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 1; i++) {
                    python_pars[i+1] = args[i];
                    Py_INCREF(args[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else if ( function->m_args_simple && 1 + 1 + function->m_defaults_given == function->m_args_positional_count ) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 1 * sizeof(PyObject *));
                memcpy(python_pars+1 + 1, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 1)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (flags & METH_NOARGS) {
#if 1 == 0
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, NULL );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(
                PyExc_TypeError,
                "%s() takes no arguments (1 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_O) {
#if 1 == 1
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, args[0] );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(PyExc_TypeError,
                "%s() takes exactly one argument (1 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_VARARGS) {
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *pos_args = MAKE_TUPLE(args, 1);

            PyObject *result;

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

#if PYTHON_VERSION < 360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 370
                result = (*(_PyCFunctionFast)method)(self, &PyTuple_GET_ITEM(pos_args, 0), 1, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 1);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                Py_DECREF(pos_args);
                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                Py_DECREF(pos_args);
                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(
            called,
            args,
            1
        );
    }

    PyObject *pos_args = MAKE_TUPLE(args, 1);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}

PyObject *CALL_FUNCTION_WITH_ARGS2(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 2; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 2 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 2; i++) {
                Py_INCREF(args[i]);
            }

            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 2 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 2 * sizeof(PyObject *));
            memcpy(python_pars + 2, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (parseArgumentsPos(function, python_pars, args, 2)) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 2 + 1 == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 2; i++) {
                    python_pars[i+1] = args[i];
                    Py_INCREF(args[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else if ( function->m_args_simple && 2 + 1 + function->m_defaults_given == function->m_args_positional_count ) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 2 * sizeof(PyObject *));
                memcpy(python_pars+1 + 2, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 2)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (flags & METH_NOARGS) {
#if 2 == 0
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, NULL );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(
                PyExc_TypeError,
                "%s() takes no arguments (2 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_O) {
#if 2 == 1
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, args[0] );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(PyExc_TypeError,
                "%s() takes exactly one argument (2 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_VARARGS) {
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *pos_args = MAKE_TUPLE(args, 2);

            PyObject *result;

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

#if PYTHON_VERSION < 360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 370
                result = (*(_PyCFunctionFast)method)(self, &PyTuple_GET_ITEM(pos_args, 0), 2, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 2);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                Py_DECREF(pos_args);
                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                Py_DECREF(pos_args);
                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(
            called,
            args,
            2
        );
    }

    PyObject *pos_args = MAKE_TUPLE(args, 2);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}

PyObject *CALL_FUNCTION_WITH_ARGS3(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 3; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 3 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 3; i++) {
                Py_INCREF(args[i]);
            }

            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 3 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 3 * sizeof(PyObject *));
            memcpy(python_pars + 3, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (parseArgumentsPos(function, python_pars, args, 3)) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 3 + 1 == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 3; i++) {
                    python_pars[i+1] = args[i];
                    Py_INCREF(args[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else if ( function->m_args_simple && 3 + 1 + function->m_defaults_given == function->m_args_positional_count ) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 3 * sizeof(PyObject *));
                memcpy(python_pars+1 + 3, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 3)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (flags & METH_NOARGS) {
#if 3 == 0
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, NULL );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(
                PyExc_TypeError,
                "%s() takes no arguments (3 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_O) {
#if 3 == 1
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, args[0] );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(PyExc_TypeError,
                "%s() takes exactly one argument (3 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_VARARGS) {
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *pos_args = MAKE_TUPLE(args, 3);

            PyObject *result;

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

#if PYTHON_VERSION < 360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 370
                result = (*(_PyCFunctionFast)method)(self, &PyTuple_GET_ITEM(pos_args, 0), 3, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 3);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                Py_DECREF(pos_args);
                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                Py_DECREF(pos_args);
                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(
            called,
            args,
            3
        );
    }

    PyObject *pos_args = MAKE_TUPLE(args, 3);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}

PyObject *CALL_FUNCTION_WITH_ARGS4(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 4; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 4 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 4; i++) {
                Py_INCREF(args[i]);
            }

            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 4 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 4 * sizeof(PyObject *));
            memcpy(python_pars + 4, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (parseArgumentsPos(function, python_pars, args, 4)) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 4 + 1 == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 4; i++) {
                    python_pars[i+1] = args[i];
                    Py_INCREF(args[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else if ( function->m_args_simple && 4 + 1 + function->m_defaults_given == function->m_args_positional_count ) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 4 * sizeof(PyObject *));
                memcpy(python_pars+1 + 4, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 4)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (flags & METH_NOARGS) {
#if 4 == 0
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, NULL );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(
                PyExc_TypeError,
                "%s() takes no arguments (4 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_O) {
#if 4 == 1
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, args[0] );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(PyExc_TypeError,
                "%s() takes exactly one argument (4 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_VARARGS) {
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *pos_args = MAKE_TUPLE(args, 4);

            PyObject *result;

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

#if PYTHON_VERSION < 360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 370
                result = (*(_PyCFunctionFast)method)(self, &PyTuple_GET_ITEM(pos_args, 0), 4, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 4);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                Py_DECREF(pos_args);
                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                Py_DECREF(pos_args);
                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(
            called,
            args,
            4
        );
    }

    PyObject *pos_args = MAKE_TUPLE(args, 4);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}

PyObject *CALL_FUNCTION_WITH_ARGS5(PyObject *called, PyObject **args) {
    CHECK_OBJECT(called);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 5; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    if (Nuitka_Function_Check(called)) {
        if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
            return NULL;
        }

        struct Nuitka_FunctionObject *function = (struct Nuitka_FunctionObject *)called;
        PyObject *result;

        if (function->m_args_simple && 5 == function->m_args_positional_count){
            for (Py_ssize_t i = 0; i < 5; i++) {
                Py_INCREF(args[i]);
            }

            result = function->m_c_code(function, args);
        } else if (function->m_args_simple && 5 + function->m_defaults_given == function->m_args_positional_count) {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
            PyObject *python_pars[function->m_args_positional_count];
#endif
            memcpy(python_pars, args, 5 * sizeof(PyObject *));
            memcpy(python_pars + 5, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

            for (Py_ssize_t i = 0; i < function->m_args_positional_count; i++) {
                Py_INCREF(python_pars[i]);
            }

            result = function->m_c_code(function, python_pars);
        } else {
#ifdef _MSC_VER
            PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
            PyObject *python_pars[function->m_args_overall_count];
#endif
            memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

            if (parseArgumentsPos(function, python_pars, args, 5)) {
                result = function->m_c_code(function, python_pars);
            } else {
                result = NULL;
            }
        }

        Py_LeaveRecursiveCall();

        return result;
    } else if (Nuitka_Method_Check(called)) {
        struct Nuitka_MethodObject *method = (struct Nuitka_MethodObject *)called;

        // Unbound method without arguments, let the error path be slow.
        if (method->m_object != NULL) {
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }

            struct Nuitka_FunctionObject *function = method->m_function;

            PyObject *result;

            if (function->m_args_simple && 5 + 1 == function->m_args_positional_count) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                for (Py_ssize_t i = 0; i < 5; i++) {
                    python_pars[i+1] = args[i];
                    Py_INCREF(args[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else if ( function->m_args_simple && 5 + 1 + function->m_defaults_given == function->m_args_positional_count ) {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_positional_count);
#else
                PyObject *python_pars[function->m_args_positional_count];
#endif
                python_pars[0] = method->m_object;
                Py_INCREF(method->m_object);

                memcpy(python_pars+1, args, 5 * sizeof(PyObject *));
                memcpy(python_pars+1 + 5, &PyTuple_GET_ITEM(function->m_defaults, 0), function->m_defaults_given * sizeof(PyObject *));

                for (Py_ssize_t i = 1; i < function->m_args_overall_count; i++) {
                    Py_INCREF(python_pars[i]);
                }

                result = function->m_c_code(function, python_pars);
            } else {
#ifdef _MSC_VER
                PyObject **python_pars = (PyObject **)_alloca(sizeof(PyObject *) * function->m_args_overall_count);
#else
                PyObject *python_pars[function->m_args_overall_count];
#endif
                memset(python_pars, 0, function->m_args_overall_count * sizeof(PyObject *));

                if (parseArgumentsMethodPos(function, python_pars, method->m_object, args, 5)) {
                    result = function->m_c_code(function, python_pars);
                } else {
                    result = NULL;
                }
            }

            Py_LeaveRecursiveCall();

            return result;
        }
    } else if (PyCFunction_Check(called)) {
        // Try to be fast about wrapping the arguments.
        int flags = PyCFunction_GET_FLAGS(called) & ~(METH_CLASS | METH_STATIC | METH_COEXIST);

        if (flags & METH_NOARGS) {
#if 5 == 0
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, NULL );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(
                PyExc_TypeError,
                "%s() takes no arguments (5 given)",
                ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_O) {
#if 5 == 1
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

            PyObject *result = (*method)( self, args[0] );

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
            // Some buggy C functions do set an error, but do not indicate it
            // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                return NULL;
            }
#else
            PyErr_Format(PyExc_TypeError,
                "%s() takes exactly one argument (5 given)",
                 ((PyCFunctionObject *)called)->m_ml->ml_name
            );
            return NULL;
#endif
        } else if (flags & METH_VARARGS) {
            PyCFunction method = PyCFunction_GET_FUNCTION(called);
            PyObject *self = PyCFunction_GET_SELF(called);

            PyObject *pos_args = MAKE_TUPLE(args, 5);

            PyObject *result;

            // Recursion guard is not strictly necessary, as we already have
            // one on our way to here.
#ifdef _NUITKA_FULL_COMPAT
            if (unlikely(Py_EnterRecursiveCall((char *)" while calling a Python object"))) {
                return NULL;
            }
#endif

#if PYTHON_VERSION < 360
            if (flags & METH_KEYWORDS) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else {
                result = (*method)(self, pos_args);
            }
#else
            if (flags == (METH_VARARGS|METH_KEYWORDS)) {
                result = (*(PyCFunctionWithKeywords)method)(self, pos_args, NULL);
            } else if (flags == METH_FASTCALL) {
#if PYTHON_VERSION < 370
                result = (*(_PyCFunctionFast)method)(self, &PyTuple_GET_ITEM(pos_args, 0), 5, NULL);
#else
                result = (*(_PyCFunctionFast)method)(self, &pos_args, 5);
#endif
            } else {
                result = (*method)(self, pos_args);
            }
#endif

#ifdef _NUITKA_FULL_COMPAT
            Py_LeaveRecursiveCall();
#endif

            if (result != NULL) {
                // Some buggy C functions do set an error, but do not indicate it
                // and Nuitka inner workings can get upset/confused from it.
                DROP_ERROR_OCCURRED();

                Py_DECREF(pos_args);
                return result;
            } else {
                // Other buggy C functions do this, return NULL, but with
                // no error set, not allowed.
                if (unlikely(!ERROR_OCCURRED())) {
                    SET_CURRENT_EXCEPTION_TYPE0_STR(
                        PyExc_SystemError,
                        "NULL result without error in PyObject_Call"
                    );
                }

                Py_DECREF(pos_args);
                return NULL;
            }
        }
    } else if (PyFunction_Check(called)) {
        return callPythonFunction(
            called,
            args,
            5
        );
    }

    PyObject *pos_args = MAKE_TUPLE(args, 5);

    PyObject *result = CALL_FUNCTION(called, pos_args, NULL);

    Py_DECREF(pos_args);

    return result;
}

PyObject *CALL_METHOD_WITH_ARGS1(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 1; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL)
        {
            Py_INCREF(descr);

#if PYTHON_VERSION < 300
            if (PyType_HasFeature(Py_TYPE(descr), Py_TPFLAGS_HAVE_CLASS)) {
#endif
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr))
                {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS1(
                        called_object,
                        args
                    );
                    Py_DECREF(called_object);
                    return result;
                }
#if PYTHON_VERSION < 300
            }
#endif
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if ( dictoffset != 0 )
        {
            // Negative dictionary offsets have special meaning.
            if ( dictoffset < 0 )
            {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0)
                    tsize = -tsize;
                size = _PyObject_VAR_SIZE( type, tsize );

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **) ((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL)
        {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = PyDict_GetItem(dict, attr_name);

            if (called_object != NULL)
            {
                Py_INCREF(called_object);
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS1(
                    called_object,
                    args
                );
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result = Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)descr,
                    source,
                    args,
                    1
                );

                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS1(
                    called_object,
                    args
                );
                Py_DECREF(called_object);

                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS1(
                descr,
                args
            );
            Py_DECREF(descr);

            return result;
        }

#if PYTHON_VERSION < 300
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            PyString_AS_STRING( attr_name )
        );
#else
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%U'",
            type->tp_name,
            attr_name
        );
#endif
        return NULL;
    }
#if PYTHON_VERSION < 300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object = GET_STRING_DICT_VALUE(
            (PyDictObject *)source_instance->in_dict,
            (PyStringObject *)attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS1(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(
            source_instance->in_class,
            attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)called_object,
                    source,
                    args,
                    1
                );
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(
                    called_object,
                    source,
                    (PyObject *)source_instance->in_class
                );

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS1(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS1(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            PyErr_Format(
                PyExc_AttributeError,
                "%s instance has no attribute '%s'",
                PyString_AS_STRING( source_instance->in_class->cl_name ),
                PyString_AS_STRING( attr_name )
            );

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {
                source,
                attr_name
            };

            called_object = CALL_FUNCTION_WITH_ARGS2(
                source_instance->in_class->cl_getattr,
                args2
            );

            if (unlikely(called_object == NULL))
            {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS1(
                called_object,
                args
            );
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(
            source,
            attr_name
        );

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS1(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(
            source,
            (char *)Nuitka_String_AsString_Unchecked(attr_name)
        );

        if (unlikely(called_object == NULL))
        {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS1(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else {
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            Nuitka_String_AsString_Unchecked(attr_name)
        );

        return NULL;
    }
}

PyObject *CALL_METHOD_WITH_ARGS2(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 2; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL)
        {
            Py_INCREF(descr);

#if PYTHON_VERSION < 300
            if (PyType_HasFeature(Py_TYPE(descr), Py_TPFLAGS_HAVE_CLASS)) {
#endif
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr))
                {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS2(
                        called_object,
                        args
                    );
                    Py_DECREF(called_object);
                    return result;
                }
#if PYTHON_VERSION < 300
            }
#endif
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if ( dictoffset != 0 )
        {
            // Negative dictionary offsets have special meaning.
            if ( dictoffset < 0 )
            {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0)
                    tsize = -tsize;
                size = _PyObject_VAR_SIZE( type, tsize );

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **) ((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL)
        {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = PyDict_GetItem(dict, attr_name);

            if (called_object != NULL)
            {
                Py_INCREF(called_object);
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(
                    called_object,
                    args
                );
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result = Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)descr,
                    source,
                    args,
                    2
                );

                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(
                    called_object,
                    args
                );
                Py_DECREF(called_object);

                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS2(
                descr,
                args
            );
            Py_DECREF(descr);

            return result;
        }

#if PYTHON_VERSION < 300
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            PyString_AS_STRING( attr_name )
        );
#else
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%U'",
            type->tp_name,
            attr_name
        );
#endif
        return NULL;
    }
#if PYTHON_VERSION < 300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object = GET_STRING_DICT_VALUE(
            (PyDictObject *)source_instance->in_dict,
            (PyStringObject *)attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS2(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(
            source_instance->in_class,
            attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)called_object,
                    source,
                    args,
                    2
                );
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(
                    called_object,
                    source,
                    (PyObject *)source_instance->in_class
                );

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS2(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS2(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            PyErr_Format(
                PyExc_AttributeError,
                "%s instance has no attribute '%s'",
                PyString_AS_STRING( source_instance->in_class->cl_name ),
                PyString_AS_STRING( attr_name )
            );

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {
                source,
                attr_name
            };

            called_object = CALL_FUNCTION_WITH_ARGS2(
                source_instance->in_class->cl_getattr,
                args2
            );

            if (unlikely(called_object == NULL))
            {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS2(
                called_object,
                args
            );
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(
            source,
            attr_name
        );

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS2(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(
            source,
            (char *)Nuitka_String_AsString_Unchecked(attr_name)
        );

        if (unlikely(called_object == NULL))
        {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS2(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else {
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            Nuitka_String_AsString_Unchecked(attr_name)
        );

        return NULL;
    }
}

PyObject *CALL_METHOD_WITH_ARGS5(PyObject *source, PyObject *attr_name, PyObject **args) {
    CHECK_OBJECT(source);
    CHECK_OBJECT(attr_name);

    // Check if arguments are valid objects in debug mode.
#ifndef __NUITKA_NO_ASSERT__
    for (size_t i = 0; i < 5; i++) {
        CHECK_OBJECT(args[i]);
    }
#endif

    PyTypeObject *type = Py_TYPE(source);

    if (type->tp_getattro == PyObject_GenericGetAttr) {
        // Unfortunately this is required, although of cause rarely necessary.
        if (unlikely(type->tp_dict == NULL)) {
            if (unlikely(PyType_Ready(type) < 0)) {
                return NULL;
            }
        }

        PyObject *descr = _PyType_Lookup(type, attr_name);
        descrgetfunc func = NULL;

        if (descr != NULL)
        {
            Py_INCREF(descr);

#if PYTHON_VERSION < 300
            if (PyType_HasFeature(Py_TYPE(descr), Py_TPFLAGS_HAVE_CLASS)) {
#endif
                func = Py_TYPE(descr)->tp_descr_get;

                if (func != NULL && PyDescr_IsData(descr))
                {
                    PyObject *called_object = func(descr, source, (PyObject *)type);
                    Py_DECREF(descr);

                    PyObject *result = CALL_FUNCTION_WITH_ARGS5(
                        called_object,
                        args
                    );
                    Py_DECREF(called_object);
                    return result;
                }
#if PYTHON_VERSION < 300
            }
#endif
        }

        Py_ssize_t dictoffset = type->tp_dictoffset;
        PyObject *dict = NULL;

        if ( dictoffset != 0 )
        {
            // Negative dictionary offsets have special meaning.
            if ( dictoffset < 0 )
            {
                Py_ssize_t tsize;
                size_t size;

                tsize = ((PyVarObject *)source)->ob_size;
                if (tsize < 0)
                    tsize = -tsize;
                size = _PyObject_VAR_SIZE( type, tsize );

                dictoffset += (long)size;
            }

            PyObject **dictptr = (PyObject **) ((char *)source + dictoffset);
            dict = *dictptr;
        }

        if (dict != NULL)
        {
            CHECK_OBJECT(dict);

            Py_INCREF(dict);

            PyObject *called_object = PyDict_GetItem(dict, attr_name);

            if (called_object != NULL)
            {
                Py_INCREF(called_object);
                Py_XDECREF(descr);
                Py_DECREF(dict);

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(
                    called_object,
                    args
                );
                Py_DECREF(called_object);
                return result;
            }

            Py_DECREF(dict);
        }

        if (func != NULL) {
            if (func == Nuitka_Function_Type.tp_descr_get) {
                PyObject *result = Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)descr,
                    source,
                    args,
                    5
                );

                Py_DECREF(descr);

                return result;
            } else {
                PyObject *called_object = func(descr, source, (PyObject *)type);
                CHECK_OBJECT(called_object);

                Py_DECREF(descr);

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(
                    called_object,
                    args
                );
                Py_DECREF(called_object);

                return result;
            }
        }

        if (descr != NULL) {
            CHECK_OBJECT(descr);

            PyObject *result = CALL_FUNCTION_WITH_ARGS5(
                descr,
                args
            );
            Py_DECREF(descr);

            return result;
        }

#if PYTHON_VERSION < 300
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            PyString_AS_STRING( attr_name )
        );
#else
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%U'",
            type->tp_name,
            attr_name
        );
#endif
        return NULL;
    }
#if PYTHON_VERSION < 300
    else if (type == &PyInstance_Type) {
        PyInstanceObject *source_instance = (PyInstanceObject *)source;

        // The special cases have their own variant on the code generation level
        // as we are called with constants only.
        assert(attr_name != const_str_plain___dict__);
        assert(attr_name != const_str_plain___class__);

        // Try the instance dict first.
        PyObject *called_object = GET_STRING_DICT_VALUE(
            (PyDictObject *)source_instance->in_dict,
            (PyStringObject *)attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            return CALL_FUNCTION_WITH_ARGS5(called_object, args);
        }

        // Then check the class dictionaries.
        called_object = FIND_ATTRIBUTE_IN_CLASS(
            source_instance->in_class,
            attr_name
        );

        // Note: The "called_object" was found without taking a reference,
        // so we need not release it in this branch.
        if (called_object != NULL) {
            descrgetfunc descr_get = Py_TYPE(called_object)->tp_descr_get;

            if (descr_get == Nuitka_Function_Type.tp_descr_get) {
                return Nuitka_CallMethodFunctionPosArgs(
                    (struct Nuitka_FunctionObject const *)called_object,
                    source,
                    args,
                    5
                );
            } else if (descr_get != NULL) {
                PyObject *method = descr_get(
                    called_object,
                    source,
                    (PyObject *)source_instance->in_class
                );

                if (unlikely(method == NULL)) {
                    return NULL;
                }

                PyObject *result = CALL_FUNCTION_WITH_ARGS5(method, args);
                Py_DECREF(method);
                return result;
            } else {
                return CALL_FUNCTION_WITH_ARGS5(called_object, args);
            }

        } else if (unlikely(source_instance->in_class->cl_getattr == NULL)) {
            PyErr_Format(
                PyExc_AttributeError,
                "%s instance has no attribute '%s'",
                PyString_AS_STRING( source_instance->in_class->cl_name ),
                PyString_AS_STRING( attr_name )
            );

            return NULL;
        } else {
            // Finally allow the "__getattr__" override to provide it or else
            // it's an error.

            PyObject *args2[] = {
                source,
                attr_name
            };

            called_object = CALL_FUNCTION_WITH_ARGS2(
                source_instance->in_class->cl_getattr,
                args2
            );

            if (unlikely(called_object == NULL))
            {
                return NULL;
            }

            PyObject *result = CALL_FUNCTION_WITH_ARGS5(
                called_object,
                args
            );
            Py_DECREF(called_object);
            return result;
        }
    }
#endif
    else if (type->tp_getattro != NULL) {
        PyObject *called_object = (*type->tp_getattro)(
            source,
            attr_name
        );

        if (unlikely(called_object == NULL)) {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS5(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else if (type->tp_getattr != NULL) {
        PyObject *called_object = (*type->tp_getattr)(
            source,
            (char *)Nuitka_String_AsString_Unchecked(attr_name)
        );

        if (unlikely(called_object == NULL))
        {
            return NULL;
        }

        PyObject *result = CALL_FUNCTION_WITH_ARGS5(
            called_object,
            args
        );
        Py_DECREF(called_object);
        return result;
    } else {
        PyErr_Format(
            PyExc_AttributeError,
            "'%s' object has no attribute '%s'",
            type->tp_name,
            Nuitka_String_AsString_Unchecked(attr_name)
        );

        return NULL;
    }
}
/* Code to register embedded modules for meta path based loading if any. */

#include "nuitka/unfreezing.h"

/* Table for lookup to find compiled or bytecode modules included in this
 * binary or module, or put along this binary as extension modules. We do
 * our own loading for each of these.
 */
extern PyObject *modulecode___main__(PyObject *);
extern PyObject *modulecode__virtualenv(PyObject *);
extern PyObject *modulecode_createTask(PyObject *);
extern PyObject *modulecode_fullTask(PyObject *);
extern PyObject *modulecode_tkinter$$45$preLoad(PyObject *);
static struct Nuitka_MetaPathBasedLoaderEntry meta_path_loader_entries[] = {
    {"__main__", modulecode___main__, 0, 0, },
    {"_asyncio", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_bisect", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_blake2", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_bz2", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_cn", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_hk", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_iso2022", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_jp", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_kr", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_codecs_tw", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_contextvars", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_crypt", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_csv", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_ctypes", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_curses", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_curses_panel", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_datetime", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_dbm", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_decimal", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_elementtree", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_gdbm", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_hashlib", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_heapq", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_json", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_lsprof", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_lzma", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_multibytecodec", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_multiprocessing", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_opcode", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_pickle", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_posixshmem", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_posixsubprocess", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_queue", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_random", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_scproxy", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_sha3", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_sha512", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_socket", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_sqlite3", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_ssl", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_statistics", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_struct", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_tkinter", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_uuid", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"_virtualenv", modulecode__virtualenv, 0, 0, },
    {"array", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"audioop", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"binascii", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"createTask", modulecode_createTask, 0, 0, },
    {"datetime", NULL, 7911, 57029, NUITKA_BYTECODE_FLAG},
    {"fcntl", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"fullTask", modulecode_fullTask, 0, 0, },
    {"functools", NULL, 64940, 27952, NUITKA_BYTECODE_FLAG},
    {"grp", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"imp", NULL, 92892, 9860, NUITKA_BYTECODE_FLAG},
    {"importlib", NULL, 102752, 3809, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"importlib.abc", NULL, 106561, 13624, NUITKA_BYTECODE_FLAG},
    {"importlib.util", NULL, 120185, 9343, NUITKA_BYTECODE_FLAG},
    {"json", NULL, 129528, 12659, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"math", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"mmap", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"os", NULL, 142187, 31448, NUITKA_BYTECODE_FLAG},
    {"pathlib", NULL, 173635, 43603, NUITKA_BYTECODE_FLAG},
    {"pkgutil", NULL, 217238, 16360, NUITKA_BYTECODE_FLAG},
    {"posixpath", NULL, 233598, 10479, NUITKA_BYTECODE_FLAG},
    {"pyexpat", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"re", NULL, 244077, 14473, NUITKA_BYTECODE_FLAG},
    {"readline", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"select", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"site", NULL, 258550, 13323, NUITKA_BYTECODE_FLAG},
    {"termios", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"threading", NULL, 271873, 40027, NUITKA_BYTECODE_FLAG},
    {"tkinter", NULL, 311900, 176053, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"tkinter-preLoad", modulecode_tkinter$$45$preLoad, 0, 0, },
    {"unicodedata", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"zlib", NULL, 0, 0, NUITKA_SHLIB_FLAG},
    {"__future__", NULL, 487953, 4182, NUITKA_BYTECODE_FLAG},
    {"_bootlocale", NULL, 492135, 1294, NUITKA_BYTECODE_FLAG},
    {"_collections_abc", NULL, 493429, 28792, NUITKA_BYTECODE_FLAG},
    {"_compat_pickle", NULL, 522221, 5552, NUITKA_BYTECODE_FLAG},
    {"_compression", NULL, 527773, 4197, NUITKA_BYTECODE_FLAG},
    {"_dummy_thread", NULL, 531970, 6088, NUITKA_BYTECODE_FLAG},
    {"_markupbase", NULL, 538058, 7841, NUITKA_BYTECODE_FLAG},
    {"_osx_support", NULL, 545899, 10363, NUITKA_BYTECODE_FLAG},
    {"_py_abc", NULL, 556262, 4721, NUITKA_BYTECODE_FLAG},
    {"_pyio", NULL, 560983, 74130, NUITKA_BYTECODE_FLAG},
    {"_sitebuiltins", NULL, 635113, 3532, NUITKA_BYTECODE_FLAG},
    {"_strptime", NULL, 638645, 16095, NUITKA_BYTECODE_FLAG},
    {"_sysconfigdata__darwin_darwin", NULL, 654740, 22160, NUITKA_BYTECODE_FLAG},
    {"_threading_local", NULL, 676900, 6497, NUITKA_BYTECODE_FLAG},
    {"_weakrefset", NULL, 683397, 7651, NUITKA_BYTECODE_FLAG},
    {"abc", NULL, 691048, 5385, NUITKA_BYTECODE_FLAG},
    {"aifc", NULL, 696433, 25525, NUITKA_BYTECODE_FLAG},
    {"argparse", NULL, 721958, 62328, NUITKA_BYTECODE_FLAG},
    {"ast", NULL, 784286, 16732, NUITKA_BYTECODE_FLAG},
    {"asynchat", NULL, 801018, 6902, NUITKA_BYTECODE_FLAG},
    {"asyncio", NULL, 807920, 801, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"asyncio.base_events", NULL, 808721, 51071, NUITKA_BYTECODE_FLAG},
    {"asyncio.base_futures", NULL, 859792, 1774, NUITKA_BYTECODE_FLAG},
    {"asyncio.base_subprocess", NULL, 861566, 9467, NUITKA_BYTECODE_FLAG},
    {"asyncio.base_tasks", NULL, 871033, 1995, NUITKA_BYTECODE_FLAG},
    {"asyncio.constants", NULL, 873028, 632, NUITKA_BYTECODE_FLAG},
    {"asyncio.coroutines", NULL, 873660, 6705, NUITKA_BYTECODE_FLAG},
    {"asyncio.events", NULL, 880365, 28108, NUITKA_BYTECODE_FLAG},
    {"asyncio.exceptions", NULL, 908473, 2549, NUITKA_BYTECODE_FLAG},
    {"asyncio.format_helpers", NULL, 911022, 2383, NUITKA_BYTECODE_FLAG},
    {"asyncio.futures", NULL, 913405, 11244, NUITKA_BYTECODE_FLAG},
    {"asyncio.locks", NULL, 924649, 16419, NUITKA_BYTECODE_FLAG},
    {"asyncio.log", NULL, 941068, 277, NUITKA_BYTECODE_FLAG},
    {"asyncio.proactor_events", NULL, 941345, 24145, NUITKA_BYTECODE_FLAG},
    {"asyncio.protocols", NULL, 965490, 8665, NUITKA_BYTECODE_FLAG},
    {"asyncio.queues", NULL, 974155, 8432, NUITKA_BYTECODE_FLAG},
    {"asyncio.runners", NULL, 982587, 1989, NUITKA_BYTECODE_FLAG},
    {"asyncio.selector_events", NULL, 984576, 29730, NUITKA_BYTECODE_FLAG},
    {"asyncio.sslproto", NULL, 1014306, 21669, NUITKA_BYTECODE_FLAG},
    {"asyncio.staggered", NULL, 1035975, 4169, NUITKA_BYTECODE_FLAG},
    {"asyncio.streams", NULL, 1040144, 20691, NUITKA_BYTECODE_FLAG},
    {"asyncio.subprocess", NULL, 1060835, 7409, NUITKA_BYTECODE_FLAG},
    {"asyncio.tasks", NULL, 1068244, 24178, NUITKA_BYTECODE_FLAG},
    {"asyncio.transports", NULL, 1092422, 12310, NUITKA_BYTECODE_FLAG},
    {"asyncio.trsock", NULL, 1104732, 8534, NUITKA_BYTECODE_FLAG},
    {"asyncio.unix_events", NULL, 1113266, 39375, NUITKA_BYTECODE_FLAG},
    {"asyncore", NULL, 1152641, 16079, NUITKA_BYTECODE_FLAG},
    {"base64", NULL, 1168720, 17122, NUITKA_BYTECODE_FLAG},
    {"bdb", NULL, 1185842, 24972, NUITKA_BYTECODE_FLAG},
    {"binhex", NULL, 1210814, 12186, NUITKA_BYTECODE_FLAG},
    {"bisect", NULL, 1223000, 2405, NUITKA_BYTECODE_FLAG},
    {"bz2", NULL, 1225405, 11496, NUITKA_BYTECODE_FLAG},
    {"cProfile", NULL, 1236901, 5385, NUITKA_BYTECODE_FLAG},
    {"calendar", NULL, 1242286, 27115, NUITKA_BYTECODE_FLAG},
    {"cgi", NULL, 1269401, 26358, NUITKA_BYTECODE_FLAG},
    {"cgitb", NULL, 1295759, 10201, NUITKA_BYTECODE_FLAG},
    {"chunk", NULL, 1305960, 4890, NUITKA_BYTECODE_FLAG},
    {"cmd", NULL, 1310850, 12677, NUITKA_BYTECODE_FLAG},
    {"code", NULL, 1323527, 9964, NUITKA_BYTECODE_FLAG},
    {"codecs", NULL, 1333491, 34007, NUITKA_BYTECODE_FLAG},
    {"codeop", NULL, 1367498, 6469, NUITKA_BYTECODE_FLAG},
    {"collections", NULL, 1373967, 46486, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"collections.abc", NULL, 493429, 28792, NUITKA_BYTECODE_FLAG},
    {"colorsys", NULL, 1420453, 3291, NUITKA_BYTECODE_FLAG},
    {"compileall", NULL, 1423744, 9461, NUITKA_BYTECODE_FLAG},
    {"concurrent", NULL, 1433205, 183, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"concurrent.futures", NULL, 1433388, 1159, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"concurrent.futures._base", NULL, 1434547, 21951, NUITKA_BYTECODE_FLAG},
    {"concurrent.futures.process", NULL, 1456498, 20351, NUITKA_BYTECODE_FLAG},
    {"concurrent.futures.thread", NULL, 1476849, 5869, NUITKA_BYTECODE_FLAG},
    {"configparser", NULL, 1482718, 45769, NUITKA_BYTECODE_FLAG},
    {"contextlib", NULL, 1528487, 20280, NUITKA_BYTECODE_FLAG},
    {"contextvars", NULL, 1548767, 294, NUITKA_BYTECODE_FLAG},
    {"copy", NULL, 1549061, 7038, NUITKA_BYTECODE_FLAG},
    {"copyreg", NULL, 1556099, 4369, NUITKA_BYTECODE_FLAG},
    {"crypt", NULL, 1560468, 3438, NUITKA_BYTECODE_FLAG},
    {"csv", NULL, 1563906, 11961, NUITKA_BYTECODE_FLAG},
    {"ctypes", NULL, 1575867, 16423, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"ctypes._aix", NULL, 1592290, 9895, NUITKA_BYTECODE_FLAG},
    {"ctypes._endian", NULL, 1602185, 1980, NUITKA_BYTECODE_FLAG},
    {"ctypes.macholib", NULL, 1604165, 350, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"ctypes.macholib.dyld", NULL, 1604515, 4459, NUITKA_BYTECODE_FLAG},
    {"ctypes.macholib.dylib", NULL, 1608974, 1967, NUITKA_BYTECODE_FLAG},
    {"ctypes.macholib.framework", NULL, 1610941, 2247, NUITKA_BYTECODE_FLAG},
    {"ctypes.util", NULL, 1613188, 7812, NUITKA_BYTECODE_FLAG},
    {"curses", NULL, 1621000, 2191, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"curses.ascii", NULL, 1623191, 4008, NUITKA_BYTECODE_FLAG},
    {"curses.has_key", NULL, 1627199, 4606, NUITKA_BYTECODE_FLAG},
    {"curses.panel", NULL, 1631805, 274, NUITKA_BYTECODE_FLAG},
    {"curses.textpad", NULL, 1632079, 5958, NUITKA_BYTECODE_FLAG},
    {"dataclasses", NULL, 1638037, 23678, NUITKA_BYTECODE_FLAG},
    {"datetime", NULL, 7911, 57029, NUITKA_BYTECODE_FLAG},
    {"dbm", NULL, 1661715, 4243, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"dbm.dumb", NULL, 1665958, 7824, NUITKA_BYTECODE_FLAG},
    {"dbm.gnu", NULL, 1673782, 254, NUITKA_BYTECODE_FLAG},
    {"dbm.ndbm", NULL, 1674036, 253, NUITKA_BYTECODE_FLAG},
    {"decimal", NULL, 1674289, 160786, NUITKA_BYTECODE_FLAG},
    {"difflib", NULL, 1835075, 59489, NUITKA_BYTECODE_FLAG},
    {"dis", NULL, 1894564, 15853, NUITKA_BYTECODE_FLAG},
    {"distutils", NULL, 1910417, 435, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"distutils.archive_util", NULL, 1910852, 6590, NUITKA_BYTECODE_FLAG},
    {"distutils.bcppcompiler", NULL, 1917442, 6574, NUITKA_BYTECODE_FLAG},
    {"distutils.ccompiler", NULL, 1924016, 33348, NUITKA_BYTECODE_FLAG},
    {"distutils.cmd", NULL, 1957364, 13999, NUITKA_BYTECODE_FLAG},
    {"distutils.command", NULL, 1971363, 594, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"distutils.command.bdist", NULL, 1971957, 3717, NUITKA_BYTECODE_FLAG},
    {"distutils.command.bdist_dumb", NULL, 1975674, 3643, NUITKA_BYTECODE_FLAG},
    {"distutils.command.bdist_rpm", NULL, 1979317, 12479, NUITKA_BYTECODE_FLAG},
    {"distutils.command.bdist_wininst", NULL, 1991796, 8540, NUITKA_BYTECODE_FLAG},
    {"distutils.command.build", NULL, 2000336, 3932, NUITKA_BYTECODE_FLAG},
    {"distutils.command.build_clib", NULL, 2004268, 4865, NUITKA_BYTECODE_FLAG},
    {"distutils.command.build_ext", NULL, 2009133, 16188, NUITKA_BYTECODE_FLAG},
    {"distutils.command.build_py", NULL, 2025321, 10531, NUITKA_BYTECODE_FLAG},
    {"distutils.command.build_scripts", NULL, 2035852, 4375, NUITKA_BYTECODE_FLAG},
    {"distutils.command.check", NULL, 2040227, 4936, NUITKA_BYTECODE_FLAG},
    {"distutils.command.clean", NULL, 2045163, 2151, NUITKA_BYTECODE_FLAG},
    {"distutils.command.config", NULL, 2047314, 10278, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install", NULL, 2057592, 13623, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install_data", NULL, 2071215, 2340, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install_egg_info", NULL, 2073555, 3047, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install_headers", NULL, 2076602, 1759, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install_lib", NULL, 2078361, 5164, NUITKA_BYTECODE_FLAG},
    {"distutils.command.install_scripts", NULL, 2083525, 2192, NUITKA_BYTECODE_FLAG},
    {"distutils.command.register", NULL, 2085717, 8506, NUITKA_BYTECODE_FLAG},
    {"distutils.command.sdist", NULL, 2094223, 14567, NUITKA_BYTECODE_FLAG},
    {"distutils.command.upload", NULL, 2108790, 4990, NUITKA_BYTECODE_FLAG},
    {"distutils.config", NULL, 2113780, 3560, NUITKA_BYTECODE_FLAG},
    {"distutils.core", NULL, 2117340, 6665, NUITKA_BYTECODE_FLAG},
    {"distutils.cygwinccompiler", NULL, 2124005, 8663, NUITKA_BYTECODE_FLAG},
    {"distutils.debug", NULL, 2132668, 245, NUITKA_BYTECODE_FLAG},
    {"distutils.dep_util", NULL, 2132913, 2765, NUITKA_BYTECODE_FLAG},
    {"distutils.dir_util", NULL, 2135678, 5874, NUITKA_BYTECODE_FLAG},
    {"distutils.dist", NULL, 2141552, 34543, NUITKA_BYTECODE_FLAG},
    {"distutils.errors", NULL, 2176095, 5301, NUITKA_BYTECODE_FLAG},
    {"distutils.extension", NULL, 2181396, 6974, NUITKA_BYTECODE_FLAG},
    {"distutils.fancy_getopt", NULL, 2188370, 10707, NUITKA_BYTECODE_FLAG},
    {"distutils.file_util", NULL, 2199077, 5984, NUITKA_BYTECODE_FLAG},
    {"distutils.filelist", NULL, 2205061, 9918, NUITKA_BYTECODE_FLAG},
    {"distutils.log", NULL, 2214979, 2366, NUITKA_BYTECODE_FLAG},
    {"distutils.msvccompiler", NULL, 2217345, 14774, NUITKA_BYTECODE_FLAG},
    {"distutils.spawn", NULL, 2232119, 5157, NUITKA_BYTECODE_FLAG},
    {"distutils.sysconfig", NULL, 2237276, 12152, NUITKA_BYTECODE_FLAG},
    {"distutils.text_file", NULL, 2249428, 8490, NUITKA_BYTECODE_FLAG},
    {"distutils.unixccompiler", NULL, 2257918, 6669, NUITKA_BYTECODE_FLAG},
    {"distutils.util", NULL, 2264587, 15597, NUITKA_BYTECODE_FLAG},
    {"distutils.version", NULL, 2280184, 7362, NUITKA_BYTECODE_FLAG},
    {"distutils.versionpredicate", NULL, 2287546, 5186, NUITKA_BYTECODE_FLAG},
    {"doctest", NULL, 2292732, 76025, NUITKA_BYTECODE_FLAG},
    {"dummy_threading", NULL, 2368757, 1161, NUITKA_BYTECODE_FLAG},
    {"email", NULL, 2369918, 1742, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"email._encoded_words", NULL, 2371660, 5737, NUITKA_BYTECODE_FLAG},
    {"email._header_value_parser", NULL, 2377397, 79984, NUITKA_BYTECODE_FLAG},
    {"email._parseaddr", NULL, 2457381, 12505, NUITKA_BYTECODE_FLAG},
    {"email._policybase", NULL, 2469886, 14861, NUITKA_BYTECODE_FLAG},
    {"email.base64mime", NULL, 2484747, 3286, NUITKA_BYTECODE_FLAG},
    {"email.charset", NULL, 2488033, 11510, NUITKA_BYTECODE_FLAG},
    {"email.contentmanager", NULL, 2499543, 7412, NUITKA_BYTECODE_FLAG},
    {"email.encoders", NULL, 2506955, 1663, NUITKA_BYTECODE_FLAG},
    {"email.errors", NULL, 2508618, 5956, NUITKA_BYTECODE_FLAG},
    {"email.feedparser", NULL, 2514574, 10693, NUITKA_BYTECODE_FLAG},
    {"email.generator", NULL, 2525267, 12533, NUITKA_BYTECODE_FLAG},
    {"email.header", NULL, 2537800, 16490, NUITKA_BYTECODE_FLAG},
    {"email.headerregistry", NULL, 2554290, 22095, NUITKA_BYTECODE_FLAG},
    {"email.iterators", NULL, 2576385, 1971, NUITKA_BYTECODE_FLAG},
    {"email.message", NULL, 2578356, 37929, NUITKA_BYTECODE_FLAG},
    {"email.mime", NULL, 2616285, 183, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"email.mime.application", NULL, 2616468, 1510, NUITKA_BYTECODE_FLAG},
    {"email.mime.audio", NULL, 2617978, 2675, NUITKA_BYTECODE_FLAG},
    {"email.mime.base", NULL, 2620653, 1092, NUITKA_BYTECODE_FLAG},
    {"email.mime.image", NULL, 2621745, 1955, NUITKA_BYTECODE_FLAG},
    {"email.mime.message", NULL, 2623700, 1333, NUITKA_BYTECODE_FLAG},
    {"email.mime.multipart", NULL, 2625033, 1553, NUITKA_BYTECODE_FLAG},
    {"email.mime.nonmultipart", NULL, 2626586, 815, NUITKA_BYTECODE_FLAG},
    {"email.mime.text", NULL, 2627401, 1362, NUITKA_BYTECODE_FLAG},
    {"email.parser", NULL, 2628763, 5773, NUITKA_BYTECODE_FLAG},
    {"email.policy", NULL, 2634536, 9709, NUITKA_BYTECODE_FLAG},
    {"email.quoprimime", NULL, 2644245, 7729, NUITKA_BYTECODE_FLAG},
    {"email.utils", NULL, 2651974, 9593, NUITKA_BYTECODE_FLAG},
    {"encodings", NULL, 2661567, 3954, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"encodings.aliases", NULL, 2665521, 6381, NUITKA_BYTECODE_FLAG},
    {"encodings.ascii", NULL, 2671902, 1932, NUITKA_BYTECODE_FLAG},
    {"encodings.base64_codec", NULL, 2673834, 2450, NUITKA_BYTECODE_FLAG},
    {"encodings.big5", NULL, 2676284, 1460, NUITKA_BYTECODE_FLAG},
    {"encodings.big5hkscs", NULL, 2677744, 1470, NUITKA_BYTECODE_FLAG},
    {"encodings.bz2_codec", NULL, 2679214, 3341, NUITKA_BYTECODE_FLAG},
    {"encodings.charmap", NULL, 2682555, 2942, NUITKA_BYTECODE_FLAG},
    {"encodings.cp037", NULL, 2685497, 2473, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1006", NULL, 2687970, 2549, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1026", NULL, 2690519, 2477, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1125", NULL, 2692996, 8180, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1140", NULL, 2701176, 2463, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1250", NULL, 2703639, 2500, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1251", NULL, 2706139, 2497, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1252", NULL, 2708636, 2500, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1253", NULL, 2711136, 2513, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1254", NULL, 2713649, 2502, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1255", NULL, 2716151, 2521, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1256", NULL, 2718672, 2499, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1257", NULL, 2721171, 2507, NUITKA_BYTECODE_FLAG},
    {"encodings.cp1258", NULL, 2723678, 2505, NUITKA_BYTECODE_FLAG},
    {"encodings.cp273", NULL, 2726183, 2459, NUITKA_BYTECODE_FLAG},
    {"encodings.cp424", NULL, 2728642, 2503, NUITKA_BYTECODE_FLAG},
    {"encodings.cp437", NULL, 2731145, 7897, NUITKA_BYTECODE_FLAG},
    {"encodings.cp500", NULL, 2739042, 2473, NUITKA_BYTECODE_FLAG},
    {"encodings.cp720", NULL, 2741515, 2570, NUITKA_BYTECODE_FLAG},
    {"encodings.cp737", NULL, 2744085, 8219, NUITKA_BYTECODE_FLAG},
    {"encodings.cp775", NULL, 2752304, 7927, NUITKA_BYTECODE_FLAG},
    {"encodings.cp850", NULL, 2760231, 7558, NUITKA_BYTECODE_FLAG},
    {"encodings.cp852", NULL, 2767789, 7935, NUITKA_BYTECODE_FLAG},
    {"encodings.cp855", NULL, 2775724, 8188, NUITKA_BYTECODE_FLAG},
    {"encodings.cp856", NULL, 2783912, 2535, NUITKA_BYTECODE_FLAG},
    {"encodings.cp857", NULL, 2786447, 7538, NUITKA_BYTECODE_FLAG},
    {"encodings.cp858", NULL, 2793985, 7528, NUITKA_BYTECODE_FLAG},
    {"encodings.cp860", NULL, 2801513, 7876, NUITKA_BYTECODE_FLAG},
    {"encodings.cp861", NULL, 2809389, 7891, NUITKA_BYTECODE_FLAG},
    {"encodings.cp862", NULL, 2817280, 8080, NUITKA_BYTECODE_FLAG},
    {"encodings.cp863", NULL, 2825360, 7891, NUITKA_BYTECODE_FLAG},
    {"encodings.cp864", NULL, 2833251, 8035, NUITKA_BYTECODE_FLAG},
    {"encodings.cp865", NULL, 2841286, 7891, NUITKA_BYTECODE_FLAG},
    {"encodings.cp866", NULL, 2849177, 8224, NUITKA_BYTECODE_FLAG},
    {"encodings.cp869", NULL, 2857401, 7915, NUITKA_BYTECODE_FLAG},
    {"encodings.cp874", NULL, 2865316, 2601, NUITKA_BYTECODE_FLAG},
    {"encodings.cp875", NULL, 2867917, 2470, NUITKA_BYTECODE_FLAG},
    {"encodings.cp932", NULL, 2870387, 1462, NUITKA_BYTECODE_FLAG},
    {"encodings.cp949", NULL, 2871849, 1462, NUITKA_BYTECODE_FLAG},
    {"encodings.cp950", NULL, 2873311, 1462, NUITKA_BYTECODE_FLAG},
    {"encodings.euc_jis_2004", NULL, 2874773, 1476, NUITKA_BYTECODE_FLAG},
    {"encodings.euc_jisx0213", NULL, 2876249, 1476, NUITKA_BYTECODE_FLAG},
    {"encodings.euc_jp", NULL, 2877725, 1464, NUITKA_BYTECODE_FLAG},
    {"encodings.euc_kr", NULL, 2879189, 1464, NUITKA_BYTECODE_FLAG},
    {"encodings.gb18030", NULL, 2880653, 1466, NUITKA_BYTECODE_FLAG},
    {"encodings.gb2312", NULL, 2882119, 1464, NUITKA_BYTECODE_FLAG},
    {"encodings.gbk", NULL, 2883583, 1458, NUITKA_BYTECODE_FLAG},
    {"encodings.hex_codec", NULL, 2885041, 2437, NUITKA_BYTECODE_FLAG},
    {"encodings.hp_roman8", NULL, 2887478, 2674, NUITKA_BYTECODE_FLAG},
    {"encodings.hz", NULL, 2890152, 1456, NUITKA_BYTECODE_FLAG},
    {"encodings.idna", NULL, 2891608, 5668, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp", NULL, 2897276, 1477, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp_1", NULL, 2898753, 1481, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp_2", NULL, 2900234, 1481, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp_2004", NULL, 2901715, 1487, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp_3", NULL, 2903202, 1481, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_jp_ext", NULL, 2904683, 1485, NUITKA_BYTECODE_FLAG},
    {"encodings.iso2022_kr", NULL, 2906168, 1477, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_1", NULL, 2907645, 2472, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_10", NULL, 2910117, 2477, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_11", NULL, 2912594, 2571, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_13", NULL, 2915165, 2480, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_14", NULL, 2917645, 2498, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_15", NULL, 2920143, 2477, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_16", NULL, 2922620, 2479, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_2", NULL, 2925099, 2472, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_3", NULL, 2927571, 2479, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_4", NULL, 2930050, 2472, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_5", NULL, 2932522, 2473, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_6", NULL, 2934995, 2517, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_7", NULL, 2937512, 2480, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_8", NULL, 2939992, 2511, NUITKA_BYTECODE_FLAG},
    {"encodings.iso8859_9", NULL, 2942503, 2472, NUITKA_BYTECODE_FLAG},
    {"encodings.johab", NULL, 2944975, 1462, NUITKA_BYTECODE_FLAG},
    {"encodings.koi8_r", NULL, 2946437, 2524, NUITKA_BYTECODE_FLAG},
    {"encodings.koi8_t", NULL, 2948961, 2435, NUITKA_BYTECODE_FLAG},
    {"encodings.koi8_u", NULL, 2951396, 2510, NUITKA_BYTECODE_FLAG},
    {"encodings.kz1048", NULL, 2953906, 2487, NUITKA_BYTECODE_FLAG},
    {"encodings.latin_1", NULL, 2956393, 1944, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_arabic", NULL, 2958337, 7791, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_centeuro", NULL, 2966128, 2511, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_croatian", NULL, 2968639, 2519, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_cyrillic", NULL, 2971158, 2509, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_farsi", NULL, 2973667, 2453, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_greek", NULL, 2976120, 2493, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_iceland", NULL, 2978613, 2512, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_latin2", NULL, 2981125, 2653, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_roman", NULL, 2983778, 2510, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_romanian", NULL, 2986288, 2520, NUITKA_BYTECODE_FLAG},
    {"encodings.mac_turkish", NULL, 2988808, 2513, NUITKA_BYTECODE_FLAG},
    {"encodings.palmos", NULL, 2991321, 2500, NUITKA_BYTECODE_FLAG},
    {"encodings.ptcp154", NULL, 2993821, 2594, NUITKA_BYTECODE_FLAG},
    {"encodings.punycode", NULL, 2996415, 6366, NUITKA_BYTECODE_FLAG},
    {"encodings.quopri_codec", NULL, 3002781, 2466, NUITKA_BYTECODE_FLAG},
    {"encodings.raw_unicode_escape", NULL, 3005247, 1813, NUITKA_BYTECODE_FLAG},
    {"encodings.rot_13", NULL, 3007060, 3052, NUITKA_BYTECODE_FLAG},
    {"encodings.shift_jis", NULL, 3010112, 1470, NUITKA_BYTECODE_FLAG},
    {"encodings.shift_jis_2004", NULL, 3011582, 1480, NUITKA_BYTECODE_FLAG},
    {"encodings.shift_jisx0213", NULL, 3013062, 1480, NUITKA_BYTECODE_FLAG},
    {"encodings.tis_620", NULL, 3014542, 2562, NUITKA_BYTECODE_FLAG},
    {"encodings.undefined", NULL, 3017104, 2146, NUITKA_BYTECODE_FLAG},
    {"encodings.unicode_escape", NULL, 3019250, 1793, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_16", NULL, 3021043, 4923, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_16_be", NULL, 3025966, 1701, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_16_le", NULL, 3027667, 1701, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_32", NULL, 3029368, 4816, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_32_be", NULL, 3034184, 1594, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_32_le", NULL, 3035778, 1594, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_7", NULL, 3037372, 1622, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_8", NULL, 3038994, 1681, NUITKA_BYTECODE_FLAG},
    {"encodings.utf_8_sig", NULL, 3040675, 4597, NUITKA_BYTECODE_FLAG},
    {"encodings.uu_codec", NULL, 3045272, 3300, NUITKA_BYTECODE_FLAG},
    {"encodings.zlib_codec", NULL, 3048572, 3160, NUITKA_BYTECODE_FLAG},
    {"enum", NULL, 3051732, 24557, NUITKA_BYTECODE_FLAG},
    {"filecmp", NULL, 3076289, 8478, NUITKA_BYTECODE_FLAG},
    {"fileinput", NULL, 3084767, 13424, NUITKA_BYTECODE_FLAG},
    {"fnmatch", NULL, 3098191, 3383, NUITKA_BYTECODE_FLAG},
    {"formatter", NULL, 3101574, 17596, NUITKA_BYTECODE_FLAG},
    {"fractions", NULL, 3119170, 18790, NUITKA_BYTECODE_FLAG},
    {"ftplib", NULL, 3137960, 27900, NUITKA_BYTECODE_FLAG},
    {"functools", NULL, 64940, 27952, NUITKA_BYTECODE_FLAG},
    {"genericpath", NULL, 3165860, 4052, NUITKA_BYTECODE_FLAG},
    {"getopt", NULL, 3169912, 6322, NUITKA_BYTECODE_FLAG},
    {"getpass", NULL, 3176234, 4229, NUITKA_BYTECODE_FLAG},
    {"gettext", NULL, 3180463, 17934, NUITKA_BYTECODE_FLAG},
    {"glob", NULL, 3198397, 4394, NUITKA_BYTECODE_FLAG},
    {"gzip", NULL, 3202791, 18242, NUITKA_BYTECODE_FLAG},
    {"hashlib", NULL, 3221033, 6778, NUITKA_BYTECODE_FLAG},
    {"heapq", NULL, 3227811, 14121, NUITKA_BYTECODE_FLAG},
    {"hmac", NULL, 3241932, 6439, NUITKA_BYTECODE_FLAG},
    {"html", NULL, 3248371, 3669, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"html.entities", NULL, 3252040, 50580, NUITKA_BYTECODE_FLAG},
    {"html.parser", NULL, 3302620, 11249, NUITKA_BYTECODE_FLAG},
    {"http", NULL, 3313869, 6115, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"http.client", NULL, 3319984, 34737, NUITKA_BYTECODE_FLAG},
    {"http.cookiejar", NULL, 3354721, 53693, NUITKA_BYTECODE_FLAG},
    {"http.cookies", NULL, 3408414, 15319, NUITKA_BYTECODE_FLAG},
    {"http.server", NULL, 3423733, 34443, NUITKA_BYTECODE_FLAG},
    {"imaplib", NULL, 3458176, 41393, NUITKA_BYTECODE_FLAG},
    {"imghdr", NULL, 3499569, 4169, NUITKA_BYTECODE_FLAG},
    {"imp", NULL, 92892, 9860, NUITKA_BYTECODE_FLAG},
    {"importlib", NULL, 102752, 3809, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"importlib._bootstrap", NULL, 3503738, 28656, NUITKA_BYTECODE_FLAG},
    {"importlib._bootstrap_external", NULL, 3532394, 43761, NUITKA_BYTECODE_FLAG},
    {"importlib.abc", NULL, 106561, 13624, NUITKA_BYTECODE_FLAG},
    {"importlib.machinery", NULL, 3576155, 1013, NUITKA_BYTECODE_FLAG},
    {"importlib.metadata", NULL, 3577168, 20891, NUITKA_BYTECODE_FLAG},
    {"importlib.resources", NULL, 3598059, 6531, NUITKA_BYTECODE_FLAG},
    {"importlib.util", NULL, 120185, 9343, NUITKA_BYTECODE_FLAG},
    {"inspect", NULL, 3604590, 80434, NUITKA_BYTECODE_FLAG},
    {"io", NULL, 3685024, 3505, NUITKA_BYTECODE_FLAG},
    {"ipaddress", NULL, 3688529, 59619, NUITKA_BYTECODE_FLAG},
    {"json", NULL, 129528, 12659, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"json.decoder", NULL, 3748148, 9895, NUITKA_BYTECODE_FLAG},
    {"json.encoder", NULL, 3758043, 11222, NUITKA_BYTECODE_FLAG},
    {"json.scanner", NULL, 3769265, 2002, NUITKA_BYTECODE_FLAG},
    {"json.tool", NULL, 3771267, 1947, NUITKA_BYTECODE_FLAG},
    {"keyword", NULL, 3773214, 1049, NUITKA_BYTECODE_FLAG},
    {"lib2to3", NULL, 3774263, 180, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"lib2to3.btm_matcher", NULL, 3774443, 4928, NUITKA_BYTECODE_FLAG},
    {"lib2to3.btm_utils", NULL, 3779371, 6201, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixer_base", NULL, 3785572, 6304, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixer_util", NULL, 3791876, 12249, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes", NULL, 3804125, 186, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"lib2to3.fixes.fix_apply", NULL, 3804311, 1724, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_asserts", NULL, 3806035, 1323, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_basestring", NULL, 3807358, 707, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_buffer", NULL, 3808065, 852, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_dict", NULL, 3808917, 3379, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_except", NULL, 3812296, 2862, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_exec", NULL, 3815158, 1193, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_execfile", NULL, 3816351, 1741, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_exitfunc", NULL, 3818092, 2350, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_filter", NULL, 3820442, 2488, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_funcattrs", NULL, 3822930, 1020, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_future", NULL, 3823950, 828, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_getcwdu", NULL, 3824778, 832, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_has_key", NULL, 3825610, 2983, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_idioms", NULL, 3828593, 3965, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_import", NULL, 3832558, 2831, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_imports", NULL, 3835389, 4439, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_imports2", NULL, 3839828, 590, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_input", NULL, 3840418, 994, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_intern", NULL, 3841412, 1178, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_isinstance", NULL, 3842590, 1595, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_itertools", NULL, 3844185, 1594, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_itertools_imports", NULL, 3845779, 1622, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_long", NULL, 3847401, 749, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_map", NULL, 3848150, 3141, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_metaclass", NULL, 3851291, 5391, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_methodattrs", NULL, 3856682, 982, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_ne", NULL, 3857664, 855, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_next", NULL, 3858519, 3127, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_nonzero", NULL, 3861646, 967, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_numliterals", NULL, 3862613, 1067, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_operator", NULL, 3863680, 4264, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_paren", NULL, 3867944, 1434, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_print", NULL, 3869378, 2387, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_raise", NULL, 3871765, 2297, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_raw_input", NULL, 3874062, 839, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_reduce", NULL, 3874901, 1172, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_reload", NULL, 3876073, 1190, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_renames", NULL, 3877263, 2051, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_repr", NULL, 3879314, 889, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_set_literal", NULL, 3880203, 1727, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_standarderror", NULL, 3881930, 764, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_sys_exc", NULL, 3882694, 1455, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_throw", NULL, 3884149, 1852, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_tuple_params", NULL, 3886001, 4635, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_types", NULL, 3890636, 1881, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_unicode", NULL, 3892517, 1593, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_urllib", NULL, 3894110, 6043, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_ws_comma", NULL, 3900153, 1163, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_xrange", NULL, 3901316, 2573, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_xreadlines", NULL, 3903889, 1167, NUITKA_BYTECODE_FLAG},
    {"lib2to3.fixes.fix_zip", NULL, 3905056, 1627, NUITKA_BYTECODE_FLAG},
    {"lib2to3.main", NULL, 3906683, 8659, NUITKA_BYTECODE_FLAG},
    {"lib2to3.patcomp", NULL, 3915342, 5690, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2", NULL, 3921032, 216, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"lib2to3.pgen2.driver", NULL, 3921248, 5192, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.grammar", NULL, 3926440, 5716, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.literals", NULL, 3932156, 1605, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.parse", NULL, 3933761, 6549, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.pgen", NULL, 3940310, 9827, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.token", NULL, 3950137, 1938, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pgen2.tokenize", NULL, 3952075, 15323, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pygram", NULL, 3967398, 1311, NUITKA_BYTECODE_FLAG},
    {"lib2to3.pytree", NULL, 3968709, 24393, NUITKA_BYTECODE_FLAG},
    {"lib2to3.refactor", NULL, 3993102, 20491, NUITKA_BYTECODE_FLAG},
    {"linecache", NULL, 4013593, 3918, NUITKA_BYTECODE_FLAG},
    {"locale", NULL, 4017511, 34740, NUITKA_BYTECODE_FLAG},
    {"logging", NULL, 4052251, 64922, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"logging.config", NULL, 4117173, 23275, NUITKA_BYTECODE_FLAG},
    {"logging.handlers", NULL, 4140448, 43207, NUITKA_BYTECODE_FLAG},
    {"lzma", NULL, 4183655, 12069, NUITKA_BYTECODE_FLAG},
    {"mailbox", NULL, 4195724, 60315, NUITKA_BYTECODE_FLAG},
    {"mailcap", NULL, 4256039, 6527, NUITKA_BYTECODE_FLAG},
    {"mimetypes", NULL, 4262566, 16082, NUITKA_BYTECODE_FLAG},
    {"modulefinder", NULL, 4278648, 16166, NUITKA_BYTECODE_FLAG},
    {"multiprocessing", NULL, 4294814, 713, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"multiprocessing.connection", NULL, 4295527, 25285, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.context", NULL, 4320812, 13069, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.dummy", NULL, 4333881, 3954, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"multiprocessing.dummy.connection", NULL, 4337835, 2599, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.forkserver", NULL, 4340434, 8410, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.heap", NULL, 4348844, 7688, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.managers", NULL, 4356532, 41597, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.pool", NULL, 4398129, 25076, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.popen_fork", NULL, 4423205, 2695, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.popen_forkserver", NULL, 4425900, 2468, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.popen_spawn_posix", NULL, 4428368, 2259, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.process", NULL, 4430627, 11052, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.queues", NULL, 4441679, 9605, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.reduction", NULL, 4451284, 8254, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.resource_sharer", NULL, 4459538, 5307, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.resource_tracker", NULL, 4464845, 5236, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.shared_memory", NULL, 4470081, 14367, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.sharedctypes", NULL, 4484448, 7100, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.spawn", NULL, 4491548, 6747, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.synchronize", NULL, 4498295, 11341, NUITKA_BYTECODE_FLAG},
    {"multiprocessing.util", NULL, 4509636, 11537, NUITKA_BYTECODE_FLAG},
    {"netrc", NULL, 4521173, 3828, NUITKA_BYTECODE_FLAG},
    {"nntplib", NULL, 4525001, 34025, NUITKA_BYTECODE_FLAG},
    {"ntpath", NULL, 4559026, 14708, NUITKA_BYTECODE_FLAG},
    {"nturl2path", NULL, 4573734, 1652, NUITKA_BYTECODE_FLAG},
    {"numbers", NULL, 4575386, 12253, NUITKA_BYTECODE_FLAG},
    {"opcode", NULL, 4587639, 5471, NUITKA_BYTECODE_FLAG},
    {"operator", NULL, 4593110, 13742, NUITKA_BYTECODE_FLAG},
    {"optparse", NULL, 4606852, 48108, NUITKA_BYTECODE_FLAG},
    {"os", NULL, 142187, 31448, NUITKA_BYTECODE_FLAG},
    {"pathlib", NULL, 173635, 43603, NUITKA_BYTECODE_FLAG},
    {"pdb", NULL, 4654960, 47243, NUITKA_BYTECODE_FLAG},
    {"pickle", NULL, 4702203, 46930, NUITKA_BYTECODE_FLAG},
    {"pickletools", NULL, 4749133, 67255, NUITKA_BYTECODE_FLAG},
    {"pipes", NULL, 4816388, 7846, NUITKA_BYTECODE_FLAG},
    {"pkgutil", NULL, 217238, 16360, NUITKA_BYTECODE_FLAG},
    {"platform", NULL, 4824234, 24291, NUITKA_BYTECODE_FLAG},
    {"plistlib", NULL, 4848525, 26704, NUITKA_BYTECODE_FLAG},
    {"poplib", NULL, 4875229, 13510, NUITKA_BYTECODE_FLAG},
    {"posixpath", NULL, 233598, 10479, NUITKA_BYTECODE_FLAG},
    {"pprint", NULL, 4888739, 16332, NUITKA_BYTECODE_FLAG},
    {"profile", NULL, 4905071, 14665, NUITKA_BYTECODE_FLAG},
    {"pstats", NULL, 4919736, 22104, NUITKA_BYTECODE_FLAG},
    {"pty", NULL, 4941840, 4006, NUITKA_BYTECODE_FLAG},
    {"py_compile", NULL, 4945846, 7445, NUITKA_BYTECODE_FLAG},
    {"pyclbr", NULL, 4953291, 10502, NUITKA_BYTECODE_FLAG},
    {"pydoc", NULL, 4963793, 84138, NUITKA_BYTECODE_FLAG},
    {"pydoc_data", NULL, 5047931, 183, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"pydoc_data.topics", NULL, 5048114, 420558, NUITKA_BYTECODE_FLAG},
    {"queue", NULL, 5468672, 10677, NUITKA_BYTECODE_FLAG},
    {"quopri", NULL, 5479349, 5799, NUITKA_BYTECODE_FLAG},
    {"random", NULL, 5485148, 20159, NUITKA_BYTECODE_FLAG},
    {"re", NULL, 244077, 14473, NUITKA_BYTECODE_FLAG},
    {"reprlib", NULL, 5505307, 5354, NUITKA_BYTECODE_FLAG},
    {"rlcompleter", NULL, 5510661, 5806, NUITKA_BYTECODE_FLAG},
    {"runpy", NULL, 5516467, 8232, NUITKA_BYTECODE_FLAG},
    {"sched", NULL, 5524699, 6583, NUITKA_BYTECODE_FLAG},
    {"secrets", NULL, 5531282, 2241, NUITKA_BYTECODE_FLAG},
    {"selectors", NULL, 5533523, 16986, NUITKA_BYTECODE_FLAG},
    {"shelve", NULL, 5550509, 9541, NUITKA_BYTECODE_FLAG},
    {"shlex", NULL, 5560050, 7587, NUITKA_BYTECODE_FLAG},
    {"shutil", NULL, 5567637, 36620, NUITKA_BYTECODE_FLAG},
    {"signal", NULL, 5604257, 2894, NUITKA_BYTECODE_FLAG},
    {"site", NULL, 258550, 13323, NUITKA_BYTECODE_FLAG},
    {"smtpd", NULL, 5607151, 26514, NUITKA_BYTECODE_FLAG},
    {"smtplib", NULL, 5633665, 35364, NUITKA_BYTECODE_FLAG},
    {"sndhdr", NULL, 5669029, 7040, NUITKA_BYTECODE_FLAG},
    {"socket", NULL, 5676069, 27838, NUITKA_BYTECODE_FLAG},
    {"socketserver", NULL, 5703907, 24058, NUITKA_BYTECODE_FLAG},
    {"sqlite3", NULL, 5727965, 211, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"sqlite3.dbapi2", NULL, 5728176, 2555, NUITKA_BYTECODE_FLAG},
    {"sqlite3.dump", NULL, 5730731, 1980, NUITKA_BYTECODE_FLAG},
    {"sre_compile", NULL, 5732711, 15193, NUITKA_BYTECODE_FLAG},
    {"sre_constants", NULL, 5747904, 6410, NUITKA_BYTECODE_FLAG},
    {"sre_parse", NULL, 5754314, 21698, NUITKA_BYTECODE_FLAG},
    {"ssl", NULL, 5776012, 44647, NUITKA_BYTECODE_FLAG},
    {"stat", NULL, 5820659, 4423, NUITKA_BYTECODE_FLAG},
    {"statistics", NULL, 5825082, 33704, NUITKA_BYTECODE_FLAG},
    {"string", NULL, 5858786, 7351, NUITKA_BYTECODE_FLAG},
    {"stringprep", NULL, 5866137, 11068, NUITKA_BYTECODE_FLAG},
    {"struct", NULL, 5877205, 381, NUITKA_BYTECODE_FLAG},
    {"subprocess", NULL, 5877586, 41991, NUITKA_BYTECODE_FLAG},
    {"sunau", NULL, 5919577, 17131, NUITKA_BYTECODE_FLAG},
    {"symbol", NULL, 5936708, 2455, NUITKA_BYTECODE_FLAG},
    {"symtable", NULL, 5939163, 11127, NUITKA_BYTECODE_FLAG},
    {"sysconfig", NULL, 5950290, 15671, NUITKA_BYTECODE_FLAG},
    {"tabnanny", NULL, 5965961, 7081, NUITKA_BYTECODE_FLAG},
    {"tarfile", NULL, 5973042, 62631, NUITKA_BYTECODE_FLAG},
    {"telnetlib", NULL, 6035673, 18288, NUITKA_BYTECODE_FLAG},
    {"tempfile", NULL, 6053961, 23506, NUITKA_BYTECODE_FLAG},
    {"textwrap", NULL, 6077467, 13570, NUITKA_BYTECODE_FLAG},
    {"this", NULL, 6091037, 1312, NUITKA_BYTECODE_FLAG},
    {"threading", NULL, 271873, 40027, NUITKA_BYTECODE_FLAG},
    {"timeit", NULL, 6092349, 11828, NUITKA_BYTECODE_FLAG},
    {"tkinter", NULL, 311900, 176053, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"tkinter.colorchooser", NULL, 6104177, 1176, NUITKA_BYTECODE_FLAG},
    {"tkinter.commondialog", NULL, 6105353, 1173, NUITKA_BYTECODE_FLAG},
    {"tkinter.constants", NULL, 6106526, 1705, NUITKA_BYTECODE_FLAG},
    {"tkinter.dialog", NULL, 6108231, 1523, NUITKA_BYTECODE_FLAG},
    {"tkinter.dnd", NULL, 6109754, 11313, NUITKA_BYTECODE_FLAG},
    {"tkinter.filedialog", NULL, 6121067, 12279, NUITKA_BYTECODE_FLAG},
    {"tkinter.font", NULL, 6133346, 6248, NUITKA_BYTECODE_FLAG},
    {"tkinter.messagebox", NULL, 6139594, 3042, NUITKA_BYTECODE_FLAG},
    {"tkinter.scrolledtext", NULL, 6142636, 2228, NUITKA_BYTECODE_FLAG},
    {"tkinter.simpledialog", NULL, 6144864, 10667, NUITKA_BYTECODE_FLAG},
    {"tkinter.tix", NULL, 6155531, 79569, NUITKA_BYTECODE_FLAG},
    {"tkinter.ttk", NULL, 6235100, 56808, NUITKA_BYTECODE_FLAG},
    {"token", NULL, 6291908, 2536, NUITKA_BYTECODE_FLAG},
    {"tokenize", NULL, 6294444, 17211, NUITKA_BYTECODE_FLAG},
    {"trace", NULL, 6311655, 20077, NUITKA_BYTECODE_FLAG},
    {"traceback", NULL, 6331732, 19940, NUITKA_BYTECODE_FLAG},
    {"tracemalloc", NULL, 6351672, 17414, NUITKA_BYTECODE_FLAG},
    {"tty", NULL, 6369086, 1127, NUITKA_BYTECODE_FLAG},
    {"turtle", NULL, 6370213, 129991, NUITKA_BYTECODE_FLAG},
    {"types", NULL, 6500204, 9228, NUITKA_BYTECODE_FLAG},
    {"typing", NULL, 6509432, 62471, NUITKA_BYTECODE_FLAG},
    {"unittest", NULL, 6571903, 3177, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"unittest.async_case", NULL, 6575080, 4191, NUITKA_BYTECODE_FLAG},
    {"unittest.case", NULL, 6579271, 50535, NUITKA_BYTECODE_FLAG},
    {"unittest.loader", NULL, 6629806, 14587, NUITKA_BYTECODE_FLAG},
    {"unittest.main", NULL, 6644393, 7585, NUITKA_BYTECODE_FLAG},
    {"unittest.mock", NULL, 6651978, 77417, NUITKA_BYTECODE_FLAG},
    {"unittest.result", NULL, 6729395, 7342, NUITKA_BYTECODE_FLAG},
    {"unittest.runner", NULL, 6736737, 7067, NUITKA_BYTECODE_FLAG},
    {"unittest.signals", NULL, 6743804, 2271, NUITKA_BYTECODE_FLAG},
    {"unittest.suite", NULL, 6746075, 9986, NUITKA_BYTECODE_FLAG},
    {"unittest.util", NULL, 6756061, 4482, NUITKA_BYTECODE_FLAG},
    {"urllib", NULL, 6760543, 179, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"urllib.error", NULL, 6760722, 2860, NUITKA_BYTECODE_FLAG},
    {"urllib.parse", NULL, 6763582, 33983, NUITKA_BYTECODE_FLAG},
    {"urllib.request", NULL, 6797565, 72582, NUITKA_BYTECODE_FLAG},
    {"urllib.response", NULL, 6870147, 3340, NUITKA_BYTECODE_FLAG},
    {"urllib.robotparser", NULL, 6873487, 7378, NUITKA_BYTECODE_FLAG},
    {"uu", NULL, 6880865, 3656, NUITKA_BYTECODE_FLAG},
    {"uuid", NULL, 6884521, 23717, NUITKA_BYTECODE_FLAG},
    {"venv", NULL, 6908238, 14482, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"warnings", NULL, 6922720, 13703, NUITKA_BYTECODE_FLAG},
    {"wave", NULL, 6936423, 18200, NUITKA_BYTECODE_FLAG},
    {"weakref", NULL, 6954623, 19569, NUITKA_BYTECODE_FLAG},
    {"webbrowser", NULL, 6974192, 17149, NUITKA_BYTECODE_FLAG},
    {"wsgiref", NULL, 6991341, 775, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"wsgiref.handlers", NULL, 6992116, 16497, NUITKA_BYTECODE_FLAG},
    {"wsgiref.headers", NULL, 7008613, 7807, NUITKA_BYTECODE_FLAG},
    {"wsgiref.simple_server", NULL, 7016420, 5312, NUITKA_BYTECODE_FLAG},
    {"wsgiref.util", NULL, 7021732, 5463, NUITKA_BYTECODE_FLAG},
    {"wsgiref.validate", NULL, 7027195, 14806, NUITKA_BYTECODE_FLAG},
    {"xdrlib", NULL, 7042001, 8272, NUITKA_BYTECODE_FLAG},
    {"xml", NULL, 7050273, 743, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xml.dom", NULL, 7051016, 5581, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xml.dom.NodeFilter", NULL, 7056597, 1018, NUITKA_BYTECODE_FLAG},
    {"xml.dom.domreg", NULL, 7057615, 2901, NUITKA_BYTECODE_FLAG},
    {"xml.dom.expatbuilder", NULL, 7060516, 27392, NUITKA_BYTECODE_FLAG},
    {"xml.dom.minicompat", NULL, 7087908, 2793, NUITKA_BYTECODE_FLAG},
    {"xml.dom.minidom", NULL, 7090701, 55425, NUITKA_BYTECODE_FLAG},
    {"xml.dom.pulldom", NULL, 7146126, 10742, NUITKA_BYTECODE_FLAG},
    {"xml.dom.xmlbuilder", NULL, 7156868, 12545, NUITKA_BYTECODE_FLAG},
    {"xml.etree", NULL, 7169413, 182, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xml.etree.ElementInclude", NULL, 7169595, 1630, NUITKA_BYTECODE_FLAG},
    {"xml.etree.ElementPath", NULL, 7171225, 8485, NUITKA_BYTECODE_FLAG},
    {"xml.etree.ElementTree", NULL, 7179710, 55663, NUITKA_BYTECODE_FLAG},
    {"xml.etree.cElementTree", NULL, 7235373, 224, NUITKA_BYTECODE_FLAG},
    {"xml.parsers", NULL, 7235597, 356, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xml.parsers.expat", NULL, 7235953, 385, NUITKA_BYTECODE_FLAG},
    {"xml.sax", NULL, 7236338, 3270, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xml.sax._exceptions", NULL, 7239608, 5495, NUITKA_BYTECODE_FLAG},
    {"xml.sax.expatreader", NULL, 7245103, 12546, NUITKA_BYTECODE_FLAG},
    {"xml.sax.handler", NULL, 7257649, 12473, NUITKA_BYTECODE_FLAG},
    {"xml.sax.saxutils", NULL, 7270122, 12970, NUITKA_BYTECODE_FLAG},
    {"xml.sax.xmlreader", NULL, 7283092, 16895, NUITKA_BYTECODE_FLAG},
    {"xmlrpc", NULL, 7299987, 179, NUITKA_BYTECODE_FLAG | NUITKA_PACKAGE_FLAG},
    {"xmlrpc.client", NULL, 7300166, 34590, NUITKA_BYTECODE_FLAG},
    {"xmlrpc.server", NULL, 7334756, 29459, NUITKA_BYTECODE_FLAG},
    {"zipapp", NULL, 7364215, 5905, NUITKA_BYTECODE_FLAG},
    {"zipfile", NULL, 7370120, 58519, NUITKA_BYTECODE_FLAG},
    {NULL, NULL, 0, 0, 0}
};

void setupMetaPathBasedLoader(void) {
    static bool init_done = false;

    if (init_done == false) {
        registerMetaPathBasedUnfreezer(meta_path_loader_entries);
        init_done = true;
    }
}
