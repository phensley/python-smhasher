
// License: MIT License
// http://www.opensource.org/licenses/mit-license.php

// SMHasher code is from SMHasher project, authored by Austin Appleby, et al.
// http://code.google.com/p/smhasher/

// Python extension code by Patrick Hensley


#include <Python.h>
#include "MurmurHash3.h"


static PyObject *
py_murmur3_x86_64(PyObject *self, PyObject *args)
{
    const char *key;
    Py_ssize_t len;
    uint32_t seed = 0;
    uint64_t out[2];

    if (!PyArg_ParseTuple(args, "s#|I", &key, &len, &seed)) {
        return NULL;
    }
    MurmurHash3_x86_128((void *)key, len, seed, &out);
    // return the first 64 bits
    return PyLong_FromUnsignedLongLong(out[0]);
}


static PyObject *
py_murmur3_x64_64(PyObject *self, PyObject *args)
{
    const char *key;
    Py_ssize_t len;
    uint32_t seed = 0;
    uint64_t out[2];

    if (!PyArg_ParseTuple(args, "s#|I", &key, &len, &seed)) {
        return NULL;
    }
    MurmurHash3_x64_128((void *)key, len, seed, &out);
    // return the first 64 bits
    return PyLong_FromUnsignedLongLong(out[0]);
}

PyDoc_STRVAR(module_doc, "Python wrapper for the SMHasher routines.");

static PyMethodDef smhasher_methods[] = {
    {"murmur3_x86_64", py_murmur3_x86_64, METH_VARARGS, "Make x86 64-bit hash"},
    {"murmur3_x64_64", py_murmur3_x64_64, METH_VARARGS, "Make x64 64-bit hash"},
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

