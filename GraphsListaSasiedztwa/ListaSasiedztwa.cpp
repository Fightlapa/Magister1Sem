#include "stdafx.h"
#include <Python.h>

PyMethodDef simplestFunctions[] =
{
    /*
    *  Structures which define functions ("methods") provided by the module.
    *  Empty in this case.
    */
};


struct PyModuleDef simplestModule =
{
    /*
    *  Structure which defines the module.
    *
    *  For more info look at: https://docs.python.org/3/c-api/module.html
    *
    */
    PyModuleDef_HEAD_INIT,
    "simple_graphs",             // Name of the module.

    NULL,                   // Docstring for the module - in this case empty.

    -1,                     // Used by sub-interpreters, if you do not know what
                            // it is then you do not need it, keep -1 .

    simplestFunctions       // Structures of type `PyMethodDef` with functions
                            // (or "methods") provided by the module.
};


PyMODINIT_FUNC PyInit_simple_graphs(void)
{
    /*
    *   Function which initialises the Python module.
    *
    *   Note:  This function must be named "PyInit_MODULENAME",
    *          where "MODULENAME" is the name of the module.
    *
    */
    return PyModule_Create(&simplestModule);
}