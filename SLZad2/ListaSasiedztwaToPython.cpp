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
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

//#include "ListaSasiedztwaCpp.h"
#define ERROR return NULL;

PyObject *G6Error;
PyObject *NoVerticesError;
PyObject *TooManyVerticesError;

typedef struct {
    PyObject_HEAD
    size_t __order;  /* the maximum number of elements in q_elements */
    std::vector<std::vector<int>> AdjencyList;  /* the elements in the queue as a Python list */
} ListaSasiedztwa;

/* function implementations */
static
PyObject* order(ListaSasiedztwa* self)
{
    return PyLong_FromSize_t(self->__order);
}

static
PyObject* addVertex(ListaSasiedztwa* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    if (self->__order == 16)
    {
        PyErr_SetString(TooManyVerticesError, "too many vertices");
        ERROR
    }
    std::vector<int> vertexList;
    self->AdjencyList.push_back(vertexList);
    return NULL;
}

static
PyObject* deleteVertex(ListaSasiedztwa* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    if (self->__order == 1)
    {
        PyErr_SetString(NoVerticesError, "graph must have vertices");
        ERROR
    }
    for (std::vector<int> vertexAdjencyList : self->AdjencyList)
    {
        vertexAdjencyList.erase(remove(vertexAdjencyList.begin(), vertexAdjencyList.end(), u), vertexAdjencyList.end());
    }
    std::vector<std::vector<int>>::iterator it;
    it = self->AdjencyList.begin();
    advance(it, u);
    self->AdjencyList.erase(it);
    return NULL;
}

static
PyObject* isEdge(ListaSasiedztwa* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    if (std::find(self->AdjencyList.at(u).begin(), self->AdjencyList.at(u).end(), v) != self->AdjencyList.at(u).end())
        return Py_True;
    return Py_False;
}

static
PyObject* addEdge(ListaSasiedztwa* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    self->AdjencyList.at(u).push_back(v);
    self->AdjencyList.at(v).push_back(u);
    return NULL;
}
static
PyObject* deleteEdge(ListaSasiedztwa* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    self->AdjencyList.at(u).erase(remove(self->AdjencyList.at(u).begin(), self->AdjencyList.at(u).end(), v), self->AdjencyList.at(u).end());
    self->AdjencyList.at(v).erase(remove(self->AdjencyList.at(v).begin(), self->AdjencyList.at(v).end(), u), self->AdjencyList.at(v).end());

    return NULL;
}

static
PyObject* fromString(ListaSasiedztwa* self, PyObject* args)
{
    // Arguments passed from Python
    const char* text;    // ListaSasiedztwa color

                         // Process arguments passes from Python

    PyArg_ParseTuple(args, "s",
        &text);

    if (strlen(text) == 0)
    {
        PyErr_SetString(G6Error, "too short text");
        ERROR
    }

    int k = 0;
    self->__order = text[0] - 63;
    if (self->__order < 1 || self->__order > 16)
    {
        std::stringstream ss;
        ss << "wrong order: " << std::to_string(self->__order + 63);
        const char* converted = ss.str().c_str();
        PyErr_SetString(G6Error, converted);
        ERROR
    }

    for (int i = 0; i < self->__order; i++)
    {
        std::vector<int> newList;
        self->AdjencyList.push_back(newList);
    }

    for (int charIndex = 1; charIndex < self->__order; charIndex++) {
        int c = text[charIndex] - 63;

        for (int v = 0; v < self->__order; v++)
        {
            for (int u = 0; u < v; u++)
            {
                try
                {
                    if (k == 0)
                        c = text[charIndex] - 63;
                    if (c < 0 || c > 63)
                    {
                        std::stringstream ss;
                        ss << "wrong character: " << std::to_string(c + 63);
                        const char* converted = ss.str().c_str();
                        PyErr_SetString(G6Error, converted);
                        ERROR
                    }
                    k = 6;
                    k -= 1;
                    if ((c & (1 << k)) != 0)
                    {
                        addEdge(self, Py_BuildValue("ii", u, v));
                    }
                }
                catch(...)
                {
                    PyErr_SetString(G6Error, "too short text");
                    ERROR
                }
            }
        }
        try
        {
            c = text[charIndex];
            PyErr_SetString(G6Error, "too long text");
            ERROR
        }
        catch(...)
        {
            
        }
    }

    // Return nothing
    return NULL;
}
static
PyObject* __str__(ListaSasiedztwa* self, PyObject* args)
{
    int k = 0;
    int c = 0;
    char* text = new char[1];
    char* char_type = new char[std::to_string(self->__order + 63).length()];
    strcpy(char_type, std::to_string(self->__order + 63).c_str());

    for (int v = 0; v < self->__order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (isEdge(self, Py_BuildValue("ii", u, v)))
            {
                c |= (1 << k);
            }
            if (k == 0)
            {
                text = strcat(text, std::to_string(c + 63).c_str());
                k = 6;
                c = 0;
            }
            k -= 1;
        }
    }
    if (k != 5)
        text = strcat(text, std::to_string(c + 63).c_str());
    return PyUnicode_FromString(text);
}

static
PyObject* __eq__(ListaSasiedztwa* self, PyObject* args)
{

    PyObject* other;   // Capsule with the pointer to `ListaSasiedztwa` object
    // Process arguments
    PyArg_ParseTuple(args, "O",
        &other);

    ListaSasiedztwa* otherGraph = (ListaSasiedztwa*)PyCapsule_GetPointer(other, "ListaSasiedztwaPtr");

    //PyLongObject* thisOrder = (PyLongObject*)(PyLong_FromSize_t(self->__order));

    if (self->__order != otherGraph->__order)
        return Py_False;

    for (int v = 0; v < self->__order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (isEdge(self, Py_BuildValue("ii", u, v)) != isEdge(otherGraph, Py_BuildValue("ii", u, v)))
            {
                return Py_False;
            }
        }
    }
    return Py_True;
}
static
PyObject* __ne__(ListaSasiedztwa* self, PyObject* args)
{

    if (__eq__(self, args))
        return Py_False;
    Py_True;
}


//static int
//ListaSasiedztwa_tp_traverse(ListaSasiedztwa *self, visitproc visit, void *arg)
//{
//    Py_VISIT(self->__order);
//    Py_VISIT(self->AdjencyList);
//    return 0;
//}

//static int
//ListaSasiedztwa_tp_clear(ListaSasiedztwa *self)
//{
//    Py_CLEAR(self->__order);
//    Py_CLEAR(self->AdjencyList);
//    return 0;
//}

static void delete_object(ListaSasiedztwa* self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}



PyMethodDef cListaSasiedztwaFunctions[] =
{
    /*
    *  Structures which define functions ("methods") provided by the module.
    */

{ "order",                     // C++/Py wrapper for `fuel_up`
(PyCFunction)order, METH_NOARGS,
"Fuel up graph" },

{ "addVertex",                       // C++/Py wrapper for `drive`
(PyCFunction)addVertex, METH_VARARGS,
"Drive the graph" },

{ "deleteVertex",               // C++/Py wrapper for `print_mileage`
(PyCFunction)deleteVertex, METH_VARARGS,
"Print mileage of the graph" },

{ "isEdge",               // C++/Py wrapper for `print_mileage`
(PyCFunction)isEdge, METH_VARARGS,
"Print mileage of the graph" },

{ "addEdge",               // C++/Py wrapper for `print_mileage`
(PyCFunction)addEdge, METH_VARARGS,
"Print mileage of the graph" },

{ "deleteEdge",               // C++/Py wrapper for `print_mileage`
(PyCFunction)deleteEdge, METH_VARARGS,
"Print mileage of the graph" },

{ "fromString",               // C++/Py wrapper for `print_mileage`
(PyCFunction)fromString, METH_VARARGS,
"Print mileage of the graph" },

{ "__str__",               // C++/Py wrapper for `print_mileage`
(PyCFunction)__str__, METH_VARARGS,
"Print mileage of the graph" },

{ "__eq__",               // C++/Py wrapper for `print_mileage`
(PyCFunction)__eq__, METH_VARARGS,
"Print mileage of the graph" },

{ "__ne__",               // C++/Py wrapper for `print_mileage`
(PyCFunction)__ne__, METH_VARARGS,
"Print mileage of the graph" },

{ NULL }      // Last function description must be empty.
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


//static PyMemberDef Foo_members[] = {
//    { "__order", T_INT, offsetof(ListaSasiedztwa, __order), 0, "order attribute" },
//{ "AdjencyList", T_OBJECT_EX, offsetof(ListaSasiedztwa, AdjencyList), 0, "list attribute" },
//{ NULL }
//};


static int ListaSasiedztwa_tp_init(ListaSasiedztwa *self, PyObject *args)
{
    fromString(self, args);
    return 0;
    //if (PyArg_ParseTuple(args, "s", text)) {
    //    fromString(self, Py_BuildValue("s", text));
    //    return 0;
    //}
    //else
    //{
    //    std::cout << "ParsingTuple failed in fromString";
    //}
}

static PyObject *ListaSasiedztwa_tp_new(
    PyTypeObject *type, PyObject *args) {
    return type->tp_alloc(type, 0);
}

static PyTypeObject ListaSasiedztwaType = {
    PyVarObject_HEAD_INIT(NULL, 0)
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
    (reprfunc)__str__,                                          /* tp_str */
    0,                                          /* tp_getattro */
    0,                                          /* tp_setattro */
    0,                                          /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,                         /* tp_flags */
    0,                                  /* tp_doc */
    //(traverseproc)ListaSasiedztwa_tp_traverse,              /* tp_traverse */
    //(inquiry)ListaSasiedztwa_tp_clear,                      /* tp_clear */
    0,              /* tp_traverse */
    0,                      /* tp_clear */
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
    (initproc)ListaSasiedztwa_tp_init,                                          /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)ListaSasiedztwa_tp_new,                        /* tp_new */
};


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
    if (PyType_Ready(&ListaSasiedztwaType) < 0) return NULL;
    PyObject* m = PyModule_Create(&cSimpleGraphsModule);
    if (m == NULL) return NULL;

    G6Error = PyErr_NewException("basic_graphs.G6Error", NULL, NULL);
    Py_INCREF(G6Error);
    PyDict_SetItemString(ListaSasiedztwaType.tp_dict, "G6Error", G6Error);
    PyModule_AddObject(m, "G6Error", G6Error);


    NoVerticesError = PyErr_NewException("basic_graphs.NoVerticesError", NULL, NULL);
    Py_INCREF(NoVerticesError);
    PyDict_SetItemString(ListaSasiedztwaType.tp_dict, "NoVerticesError", NoVerticesError);
    PyModule_AddObject(m, "NoVerticesError", NoVerticesError);


    TooManyVerticesError = PyErr_NewException("basic_graphs.TooManyVerticesError", NULL, NULL);
    Py_INCREF(TooManyVerticesError);
    PyDict_SetItemString(ListaSasiedztwaType.tp_dict, "TooManyVerticesError", TooManyVerticesError);
    PyModule_AddObject(m, "TooManyVerticesError", TooManyVerticesError);


    Py_INCREF(&ListaSasiedztwaType);
    PyModule_AddObject(m, "ListaSasiedztwa",
        (PyObject *)&ListaSasiedztwaType);

    return m;
}