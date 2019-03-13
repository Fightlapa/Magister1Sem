/*
*  graph2py.cpp:
*
*  BOTTOM INTERFACE TO `CAR`.
*
*  (c) 2017, Jacek Pierzchlewski, jacek@pierzchlewski.com
*
*  License:  BSD 2-CLAUSE.
*/
#include <Python.h>
#include "structmember.h"
#include <iostream>
//#include "ListaSasiedztwaCpp.h"

typedef struct {
    PyObject_HEAD
    Py_ssize_t q__order;  /* the maximum number of elements in q_elements */
    PyObject* q_elements;  /* the elements in the queue as a Python list */
} ListaSasiedztwa;

/* function implementations */

PyObject* order(PyObject* self, PyObject* args)
{

    // Get the pointer to `ListaSasiedztwa` object
    //ListaSasiedztwa* graph = (ListaSasiedztwa*)PyCapsule_GetPointer(self, "ListaSasiedztwaPtr");
    ListaSasiedztwa* graph = (ListaSasiedztwa*)(self);


    // Return nothing
    return Py_BuildValue("i", graph->q__order);
}

//void addVertex(ListaSasiedztwa* self, PyObject* args)
//{
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    unsigned int iKM_;       // Kilomters to drive
//
//                             // Process arguments
//    PyArg_ParseTuple(args, "",
//        &graphCapsule);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//    // Call `drive` function
//    graph->addVertex();
//
//    // Return nothing
//    return;
//}
//
//void deleteVertex(ListaSasiedztwa* self, PyObject* args)
//{
//
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u;
//                             // Process arguments
//    PyArg_ParseTuple(args, "i",
//        &graphCapsule,
//        &u);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//    // Call `print_mileage` function
//    graph->deleteVertex(u);
//
//    // Return nothing
//    return;
//}
//
//bool isEdge(ListaSasiedztwa* self, PyObject* args)
//{
//
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u,v;
//    // Process arguments
//    PyArg_ParseTuple(args, "ii",
//        &graphCapsule,
//        &u,
//        &v);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//    // Return nothing
//    return graph->isEdge(u, v);
//}
//
//void addEdge(ListaSasiedztwa* self, PyObject* args)
//{
//
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u, v;
//    // Process arguments
//    PyArg_ParseTuple(args, "ii",
//        &graphCapsule,
//        &u,
//        &v);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//
//    graph->addEdge(u, v);
//
//    // Return nothing
//    return;
//}
//
//void deleteEdge(ListaSasiedztwa* self, PyObject* args)
//{
//
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u, v;
//    // Process arguments
//    PyArg_ParseTuple(args, "ii",
//        &graphCapsule,
//        &u,
//        &v);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//
//    graph->deleteEdge(u, v);
//}
//
//void fromString(ListaSasiedztwa* self, PyObject* args)
//{
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    // Arguments passed from Python
//    const char* text;    // ListaSasiedztwa color
//
//                         // Process arguments passes from Python
//    PyArg_ParseTuple(args, "s",
//        &graphCapsule,
//        &text);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//
//    graph->fromString(text);
//
//    // Return nothing
//    return;
//}
//
//const char* __str__(ListaSasiedztwa* self, PyObject* args)
//{
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//                              // Arguments passed from Python
//    const char* text;    // ListaSasiedztwa color
//
//                         // Process arguments passes from Python
//    PyArg_ParseTuple(args, "",
//        &graphCapsule);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//
//    // Return nothing
//    return graph->__str__();
//}
//
//bool __eq__(ListaSasiedztwa* self, PyObject* args)
//{
//
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    PyObject* other;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u, v;
//    // Process arguments
//    PyArg_ParseTuple(args, "O",
//        &graphCapsule,
//        &other);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//    ListaSasiedztwa* otherGraph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(other, "ListaSasiedztwaPtr");
//
//    // Return nothing
//    return graph->__eq__(*otherGraph);
//}
//
//bool __ne__(ListaSasiedztwa* self, PyObject* args)
//{
//    // Arguments passed from Python
//    PyObject* graphCapsule;   // Capsule with the pointer to `ListaSasiedztwa` object
//    PyObject* other;   // Capsule with the pointer to `ListaSasiedztwa` object
//    int u, v;
//    // Process arguments
//    PyArg_ParseTuple(args, "O",
//        &graphCapsule,
//        &other);
//
//    // Get the pointer to `ListaSasiedztwa` object
//    ListaSasiedztwaCpp* graph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(graphCapsule, "ListaSasiedztwaPtr");
//    ListaSasiedztwaCpp* otherGraph = (ListaSasiedztwaCpp*)PyCapsule_GetPointer(other, "ListaSasiedztwaPtr");
//
//    // Return nothing
//    return graph->__ne__(*otherGraph);
//}


static int
ListaSasiedztwa_tp_traverse(ListaSasiedztwa *self, visitproc visit, void *arg)
{
    Py_VISIT(self->q__order);
    Py_VISIT(self->q_elements);
    return 0;
}

static int
ListaSasiedztwa_tp_clear(ListaSasiedztwa *self)
{
    Py_CLEAR(self->q__order);
    Py_CLEAR(self->q_elements);
    return 0;
}

static void delete_object(ListaSasiedztwa* self)
{
    ListaSasiedztwa_tp_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
}



PyMethodDef cListaSasiedztwaFunctions[] =
{
    /*
    *  Structures which define functions ("methods") provided by the module.
    */

{ "order",                     // C++/Py wrapper for `fuel_up`
order, METH_VARARGS,
"Fuel up graph" },

//{ "addVertex",                       // C++/Py wrapper for `drive`
//addVertex, METH_VARARGS,
//"Drive the graph" },
//
//{ "deleteVertex",               // C++/Py wrapper for `print_mileage`
//deleteVertex, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "isEdge",               // C++/Py wrapper for `print_mileage`
//isEdge, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "addEdge",               // C++/Py wrapper for `print_mileage`
//addEdge, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "deleteEdge",               // C++/Py wrapper for `print_mileage`
//deleteEdge, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "fromString",               // C++/Py wrapper for `print_mileage`
//fromString, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "__str__",               // C++/Py wrapper for `print_mileage`
//__str__, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "__eq__",               // C++/Py wrapper for `print_mileage`
//__eq__, METH_VARARGS,
//"Print mileage of the graph" },
//
//{ "__ne__",               // C++/Py wrapper for `print_mileage`
//__ne__, METH_VARARGS,
//"Print mileage of the graph" },

{ NULL, NULL, 0, NULL }      // Last function description must be empty.
                             // Otherwise, it will create seg fault while
                             // importing the module.
};




struct PyModuleDef cSimpleGraphsModule =
{
    /*
    *  Structure which defines the module.
    *
    *  For more info look at: https://docs.python.org/3/c-api/module.html
    *
    */
    PyModuleDef_HEAD_INIT,
    "simple_graphs",               // Name of the module.

    NULL,                 // Docstring for the module - in this case empty.

    -1,                   // Used by sub-interpreters, if you do not know what
                          // it is then you do not need it, keep -1 .

    nullptr         // Structures of type `PyMethodDef` with functions
                                                // (or "methods") provided by the module.
};


static PyMemberDef Foo_members[] = {
    { "q__order", T_INT, offsetof(ListaSasiedztwa, q__order), 0, "order attribute" },
{ "q_elements", T_OBJECT_EX, offsetof(ListaSasiedztwa, q_elements), 0, "list attribute" },
{ NULL }
};


static PyObject* ListaSasiedztwa_tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);


static PyTypeObject ListaSasiedztwaType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "simple_graphs.ListaSasiedztwa",                              /* tp_name */ /* For printing, in format "<module>.<name>" */
    sizeof(ListaSasiedztwa),                              /* tp_basicsize */
    0,                                          /* tp_itemsize */
    (destructor)delete_object,                 /* tp_dealloc */
    0,                                          /* tp_print */
    0,                                          /* tp_getattr */
    0,                                          /* tp_setattr */
    0,                                          /* tp_reserved */
    0,                      /* tp_repr */
    0,                                          /* tp_as_number */
    0,                                          /* tp_as_sequence */
    0,                                          /* tp_as_mapping */
    0,                                          /* tp_hash */
    0,                                          /* tp_call */
    0,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                         /* tp_flags */
    0,                                  /* tp_doc */
    (traverseproc)ListaSasiedztwa_tp_traverse,              /* tp_traverse */
    (inquiry)ListaSasiedztwa_tp_clear,                      /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    cListaSasiedztwaFunctions,                              /* tp_methods */
    0,                                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    0,                                          /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)ListaSasiedztwa_tp_new,                        /* tp_new */
};


static PyObject* ListaSasiedztwa_tp_new(PyTypeObject *type, PyObject *args, PyObject *kwargs)
{
    ListaSasiedztwa *self = (ListaSasiedztwa *)ListaSasiedztwaType.tp_new(type, args, kwargs);
    if (!self) {
        return NULL;
    }

    return (PyObject *)self;
}

/* Add a type to a module */
int
PyModule_AddType(PyObject *module, const char *name, PyTypeObject *type)
{
    if (PyType_Ready(type)) {
        return -1;
    }
    Py_INCREF(type);
    if (PyModule_AddObject(module, name, (PyObject *)type)) {
        Py_DECREF(type);
        return -1;
    }
    return 0;
}
static PyObject* ListaSasiedztwaAtrybutModulu;
PyMODINIT_FUNC PyInit_simple_graphs(void)
{
    /*
    *   Function which initialises the Python module.
    *
    *   Note:  This function must be named "PyInit_MODULENAME",
    *          where "MODULENAME" is the name of the module.
    *
    */
    PyObject *m = PyModule_Create(&cSimpleGraphsModule);
    //ListaSasiedztwaType.tp_new = PyType_GenericNew;
    //PyModule_AddType(m, "ListaSasiedztwa", &ListaSasiedztwaType);
    //ListaSasiedztwaAtrybutModulu = PyCapsule_New(&ListaSasiedztwaAtrybutModulu, "simple_graphs.ListaSasiedztwa", NULL);
    //PyObject * ListaSasiedztwaAtrybutModuluCapsuled = ListaSasiedztwa_tp_new(&ListaSasiedztwaAtrybutModulu, nullptr, nullptr);
    ListaSasiedztwaType.tp_new = PyType_GenericNew;
    PyModule_AddType(m, "ListaSasiedztwa", &ListaSasiedztwaType);

    return m;
}