
// License: MIT License
// http://www.opensource.org/licenses/mit-license.php

// SMHasher code is from SMHasher project, authored by Austin Appleby, et al.
// http://code.google.com/p/smhasher/

// Python extension code by Patrick Hensley


#include <Python.h>
#include "MurmurHash3.h"


typedef void (*murmur3_func)(const void *, int, uint32_t, void *);


static PyObject *
_py_murmur3_64(PyObject *self, PyObject *args, murmur3_func hashfunc)
{
    const char *key;
    Py_ssize_t len;
    uint32_t seed = 0;
    uint64_t out[2];

    if (!PyArg_ParseTuple(args, "s#|I", &key, &len, &seed)) {
        return NULL;
    }
    hashfunc((void *)key, len, seed, &out);
    // return the first 64 bits
    return PyLong_FromUnsignedLongLong(out[0]);
}


static PyObject *
py_murmur3_x86_64(PyObject *self, PyObject *args)
{
    return _py_murmur3_64(self, args, MurmurHash3_x86_128);
}


static PyObject *
py_murmur3_x64_64(PyObject *self, PyObject *args)
{
    return _py_murmur3_64(self, args, MurmurHash3_x64_128);
}


static PyObject *
_py_murmur3_128(PyObject *self, PyObject *args, murmur3_func hashfunc)
{
    const char *key;
    Py_ssize_t len;
    uint32_t seed = 0;
    uint64_t out[2];
    PyNumberMethods *long_methods = PyLong_Type.tp_as_number;
    PyObject * denom = 0;
    PyObject *hi = 0;
    PyObject *lo = 0;
    PyObject *tmp = 0;
    PyObject *result = 0;

    if (!PyArg_ParseTuple(args, "s#|I", &key, &len, &seed)) {
        return NULL;
    }

    // get the hi and lo parts of the 128-bit hash value
    hashfunc((void *)key, len, seed, &out);
//    MurmurHash3_x64_128((void *)key, len, seed, &out);
    hi = PyLong_FromUnsignedLongLong(out[0]);
    lo = PyLong_FromUnsignedLongLong(out[1]);

    // result = (hi << 64) + lo
    denom = PyLong_FromLong(64);
    tmp = long_methods->nb_lshift(hi, denom);
    result = long_methods->nb_add(tmp, lo);

    Py_DECREF(denom);
    Py_DECREF(tmp);
    Py_DECREF(hi);
    Py_DECREF(lo);
    return result;
}


static PyObject *
py_murmur3_x86_128(PyObject *self, PyObject *args)
{
    return _py_murmur3_128(self, args, MurmurHash3_x86_128);
}


static PyObject *
py_murmur3_x64_128(PyObject *self, PyObject *args)
{
    return _py_murmur3_128(self, args, MurmurHash3_x64_128);
}


PyDoc_STRVAR(module_doc, "Python wrapper for the SMHasher routines.");

static PyMethodDef smhasher_methods[] = {
    {"murmur3_x86_64", py_murmur3_x86_64, METH_VARARGS,
        "Make an x86 murmur3 64-bit hash value"},
    {"murmur3_x64_64", py_murmur3_x64_64, METH_VARARGS,
        "Make an x64 murmur3 64-bit hash value"},

    {"murmur3_x86_128", py_murmur3_x86_128, METH_VARARGS,
        "Make an x86 murmur3 128-bit hash value"},
    {"murmur3_x64_128", py_murmur3_x64_128, METH_VARARGS,
        "Make an x64 murmur3 128-bit hash value"},

    {NULL, NULL, 0, NULL}
};


#if PY_MAJOR_VERSION <= 2

extern "C" PyMODINIT_FUNC
initsmhasher(void)
{
    PyObject *m;

    m = Py_InitModule3("smhasher", smhasher_methods, module_doc);

    if (m == NULL)
        return;
    PyModule_AddStringConstant(m, "__version__", MODULE_VERSION);
}

#else

/* Python 3.x */

static PyModuleDef smhasher_module = {
    PyModuleDef_HEAD_INIT,
    "smhasher",
    module_doc,
    -1,
    smhasher_methods,
    NULL,
    NULL,
    NULL,
    NULL
};

extern "C" PyMODINIT_FUNC
PyInit_smhasher(void)
{
    PyObject *m;

    m = PyModule_Create(&smhasher_module);
    if (m == NULL)
        goto finally;
    PyModule_AddStringConstant(m, "__version__", MODULE_VERSION);

finally:
    return m;
}

#endif

