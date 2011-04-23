
// License: MIT License
// http://www.opensource.org/licenses/mit-license.php

// Murmur3 code is from SMHasher project, authored by Austin Appleby
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


static PyMethodDef murmur3_methods[] = {
    {"murmur3_x86_64", py_murmur3_x86_64, METH_VARARGS, "Make x86 64-bit hash"},
    {"murmur3_x64_64", py_murmur3_x64_64, METH_VARARGS, "Make x64 64-bit hash"},
    {NULL, NULL, 0, NULL}
};


extern "C" PyMODINIT_FUNC
initmurmur3(void)
{
    PyObject *m;

    m = Py_InitModule("murmur3", murmur3_methods);
    if (m == NULL)
        return;
}


