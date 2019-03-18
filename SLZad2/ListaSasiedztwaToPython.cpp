#include <Python.h>
#include "structmember.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

//#include "AdjacencyListCpp.h"

PyObject *G6Error;
PyObject *NoVerticesError;
PyObject *TooManyVerticesError;

typedef struct {
    PyObject_HEAD
    size_t __order;  /* the maximum number of elements in q_elements */
    std::vector<std::vector<int>> __AdjacencyList;  /* the elements in the queue as a Python list */
} AdjacencyList;

/* function implementations */
static
PyObject* order(AdjacencyList* self)
{
    return PyLong_FromSize_t(self->__order);
}

static
PyObject* addVertex(AdjacencyList* self)
{
    if (self->__order == 16)
    {
        PyErr_SetString(TooManyVerticesError, "too many vertices");
        return NULL;
    }
    std::vector<int> vertexList;
    self->__AdjacencyList.push_back(vertexList);
    self->__order++;
    Py_RETURN_NONE;
}

static
PyObject* deleteVertex(AdjacencyList* self, PyObject* args)
{
    int u;
    // Process arguments
    u = _PyLong_AsInt(args);

    if (self->__order == 1)
    {
        PyErr_SetString(NoVerticesError, "graph must have vertices");
        return NULL;
    }
    for (std::vector<int> vertexAdjencyList : self->__AdjacencyList)
    {
        vertexAdjencyList.erase(remove(vertexAdjencyList.begin(), vertexAdjencyList.end(), u), vertexAdjencyList.end());
    }
    std::vector<std::vector<int>>::iterator it;
    it = self->__AdjacencyList.begin();
    advance(it, u);
    self->__AdjacencyList.erase(it);
    self->__order--;
    Py_RETURN_NONE;
}

static
PyObject* isEdge(AdjacencyList* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    if (std::find(self->__AdjacencyList.at(u).begin(), self->__AdjacencyList.at(u).end(), v) != self->__AdjacencyList.at(u).end())
        Py_RETURN_TRUE;
    Py_RETURN_FALSE;
}

static
PyObject* addEdge(AdjacencyList* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    self->__AdjacencyList.at(u).push_back(v);
    self->__AdjacencyList.at(v).push_back(u);
    Py_RETURN_NONE;
}
static
PyObject* deleteEdge(AdjacencyList* self, PyObject* args)
{
    int u, v;
    // Process arguments
    PyArg_ParseTuple(args, "ii",
        &u,
        &v);

    self->__AdjacencyList.at(u).erase(remove(self->__AdjacencyList.at(u).begin(), self->__AdjacencyList.at(u).end(), v), self->__AdjacencyList.at(u).end());
    self->__AdjacencyList.at(v).erase(remove(self->__AdjacencyList.at(v).begin(), self->__AdjacencyList.at(v).end(), u), self->__AdjacencyList.at(v).end());

    Py_RETURN_NONE;
}
static PyObject* fromStringAdapter(AdjacencyList* self, const char* text)
{
    if (strlen(text) == 0)
    {
        PyErr_SetString(G6Error, "too short text");
        return NULL;
    }

    int k = 0;
    self->__order = text[0] - 63;
    if (self->__order < 1 || self->__order > 16)
    {
        std::stringstream ss;
        ss << "wrong order: " << std::to_string(self->__order + 63);
        const char* converted = ss.str().c_str();
        PyErr_SetString(G6Error, converted);
        return NULL;
    }

    for (int i = 0; i < self->__order; i++)
    {
        std::vector<int> newList;
        self->__AdjacencyList.push_back(newList);
    }

    int charIndex = 1;
    int c;

    for (int v = 1; v < self->__order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (k == 0)
            {
                if (charIndex == strlen(text))
                {
                    PyErr_SetString(G6Error, "too short text");
                    return NULL;
                }
                c = text[charIndex++] - 63;
                if (c < 0 || c > 63)
                {
                    std::stringstream ss;
                    ss << "wrong character: " << std::to_string(c + 63);
                    const char* converted = ss.str().c_str();
                    PyErr_SetString(G6Error, converted);
                    return NULL;
                }
                k = 6;
            }
            k -= 1;
            if ((c & (1 << k)) != 0)
            {
                self->__AdjacencyList.at(u).push_back(v);
                self->__AdjacencyList.at(v).push_back(u);
            }
        }
    }

    if (charIndex != strlen(text))
    {
        PyErr_SetString(G6Error, "too long text");
        return NULL;
    }
    Py_RETURN_NONE;
}

static
PyObject* fromString(AdjacencyList* self, PyObject* args)
{
    // Arguments passed from Python
    const char* text;    // AdjacencyList color

                         // Process arguments passes from Python

    PyArg_ParseTuple(args, "s",
        &text);
    return fromStringAdapter(self, text);
}
static
PyObject* __str__(AdjacencyList* self)
{
    int k = 5;
    int c = 0;
    char* text = new char[1 + self->__order * self->__order];
    text[0] = self->__order + 63;
    int currentIndex = 0;

    for (int v = 1; v < self->__order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            if (std::find(self->__AdjacencyList.at(u).begin(), self->__AdjacencyList.at(u).end(), v) != self->__AdjacencyList.at(u).end())
            {
                c |= (1 << k);
            }
            //PyObject* temp = Py_BuildValue("ii", u, v);
            //if (isEdge(self, temp))
            //{
            //    c |= (1 << k);
            //}

            //Py_XDECREF(temp);

            if (k == 0)
            {
                text[++currentIndex] = c + 63;
                k = 6;
                c = 0;
            }
            k -= 1;
        }
    }
    if (k != 5)
        text[++currentIndex] = c + 63;
    currentIndex++;
    text[currentIndex] = 0;
    PyObject* result = PyUnicode_FromString(text);
    delete[] text;
    return result;
}

static
PyObject* __eq__(AdjacencyList* self, PyObject* args)
{

    PyObject* other;   // Capsule with the pointer to `AdjacencyList` object
    // Process arguments
    PyArg_ParseTuple(args, "O",
        &other);

    AdjacencyList* otherGraph = (AdjacencyList*)PyCapsule_GetPointer(other, "AdjacencyListPtr");

    //PyLongObject* thisOrder = (PyLongObject*)(PyLong_FromSize_t(self->__order));

    if (self->__order != otherGraph->__order)
        Py_RETURN_FALSE;

    for (int v = 0; v < self->__order; v++)
    {
        for (int u = 0; u < v; u++)
        {
            self->__AdjacencyList.at(u).push_back(v);
            self->__AdjacencyList.at(v).push_back(u);

            if ((std::find(self->__AdjacencyList.at(u).begin(), self->__AdjacencyList.at(u).end(), v) != self->__AdjacencyList.at(u).end())
                != (std::find(otherGraph->__AdjacencyList.at(u).begin(), otherGraph->__AdjacencyList.at(u).end(), v) != otherGraph->__AdjacencyList.at(u).end()))
            {
                Py_RETURN_FALSE;
            }

        }
    }
    Py_RETURN_TRUE;
}
static
PyObject* __ne__(AdjacencyList* self, PyObject* args)
{

    if (__eq__(self, args))
        Py_RETURN_FALSE;
    Py_RETURN_TRUE;
}


//static int
//AdjacencyList_tp_traverse(AdjacencyList *self, visitproc visit, void *arg)
//{
//    Py_VISIT(self->__order);
//    Py_VISIT(self->__AdjacencyList);
//    return 0;
//}

//static int
//AdjacencyList_tp_clear(AdjacencyList *self)
//{
//    Py_CLEAR(self->__order);
//    Py_CLEAR(self->__AdjacencyList);
//    return 0;
//}

static void delete_object(AdjacencyList* self)
{
    Py_TYPE(self)->tp_free((PyObject *)self);
}



PyMethodDef cAdjacencyListFunctions[] =
{
    /*
    *  Structures which define functions ("methods") provided by the module.
    */

{ "order",                     // C++/Py wrapper for `fuel_up`
(PyCFunction)order, METH_NOARGS,
"Fuel up graph" },

{ "addVertex",                       // C++/Py wrapper for `drive`
(PyCFunction)addVertex, METH_NOARGS,
"Drive the graph" },

{ "deleteVertex",               // C++/Py wrapper for `print_mileage`
(PyCFunction)deleteVertex, METH_O,
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

//{ "__str__",               // C++/Py wrapper for `print_mileage`
//(PyCFunction)__str__, METH_VARARGS,
//"Print mileage of the graph" },

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
//    { "__order", T_INT, offsetof(AdjacencyList, __order), 0, "order attribute" },
//{ "__AdjacencyList", T_OBJECT_EX, offsetof(AdjacencyList, __AdjacencyList), 0, "list attribute" },
//{ NULL }
//};


static int AdjacencyList_tp_init(AdjacencyList *self, PyObject *args)
{
    const char* text = {"@"};
    PyArg_ParseTuple(args, "|s", &text);

    PyObject *t = fromStringAdapter(self, text);
    if (t == nullptr)
    {
        return -1;
    }
    return 0;
}

static PyObject *AdjacencyList_tp_new(
    PyTypeObject *type, PyObject *args) {
    return type->tp_alloc(type, 0);
}

static PyTypeObject AdjacencyListType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "simple_graphs.AdjacencyList",                              /* tp_name */ /* For printing, in format "<module>.<name>" */
    sizeof(AdjacencyList),                              /* tp_basicsize */
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
    //(traverseproc)AdjacencyList_tp_traverse,              /* tp_traverse */
    //(inquiry)AdjacencyList_tp_clear,                      /* tp_clear */
    0,              /* tp_traverse */
    0,                      /* tp_clear */
    0,                                          /* tp_richcompare */
    0,                                          /* tp_weaklistoffset */
    0,                                          /* tp_iter */
    0,                                          /* tp_iternext */
    cAdjacencyListFunctions,                              /* tp_methods */
    0,                                          /* tp_members */
    0,                                          /* tp_getset */
    0,                                          /* tp_base */
    0,                                          /* tp_dict */
    0,                                          /* tp_descr_get */
    0,                                          /* tp_descr_set */
    0,                                          /* tp_dictoffset */
    (initproc)AdjacencyList_tp_init,                                          /* tp_init */
    0,                                          /* tp_alloc */
    (newfunc)AdjacencyList_tp_new,                        /* tp_new */
};

PyMODINIT_FUNC PyInit_simple_graphs(void)
{
    if (PyType_Ready(&AdjacencyListType) < 0) Py_RETURN_NONE;
    PyObject* m = PyModule_Create(&cSimpleGraphsModule);
    if (m == NULL) Py_RETURN_NONE;

    G6Error = PyErr_NewException("simple_graphs.AdjacencyList.G6Error", NULL, NULL);
    Py_INCREF(G6Error);
    //PyModule_AddObject(m, "AdjacencyList.G6Error", G6Error);
    PyDict_SetItemString(AdjacencyListType.tp_dict, "G6Error", G6Error);


    NoVerticesError = PyErr_NewException("simple_graphs.AdjacencyList.NoVerticesError", NULL, NULL);
    Py_INCREF(NoVerticesError);
    //PyModule_AddObject(m, "AdjacencyList.NoVerticesError", NoVerticesError);
    PyDict_SetItemString(AdjacencyListType.tp_dict, "NoVerticesError", NoVerticesError);


    TooManyVerticesError = PyErr_NewException("simple_graphs.AdjacencyList.TooManyVerticesError", NULL, NULL);
    Py_INCREF(TooManyVerticesError);
    //PyModule_AddObject(m, "AdjacencyList.TooManyVerticesError", TooManyVerticesError);
    PyDict_SetItemString(AdjacencyListType.tp_dict, "TooManyVerticesError", TooManyVerticesError);


    Py_INCREF(&AdjacencyListType);
    PyModule_AddObject(m, "AdjacencyList",
        (PyObject *)&AdjacencyListType);

    return m;
}