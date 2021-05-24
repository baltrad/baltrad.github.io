/* --------------------------------------------------------------------
Copyright (C) 2013 Swedish Meteorological and Hydrological Institute, SMHI,

This file is part of RAVE.

RAVE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RAVE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RAVE.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------*/
/**
 * Python wrapper of the hello tutorial
 * @file
 * @author Daniel Michelson (Swedish Meteorological and Hydrological Institute, SMHI)
 * @date 2013-11-15
 */
#include "Python.h"
#include "arrayobject.h"
#include "rave.h"
#include "rave_debug.h"
#include "pyraveio.h"
#include "pyrave_debug.h"
#include "hello.h"

/**
 * Debug this module
 */
PYRAVE_DEBUG_MODULE("_hello");

/**
 * Sets a Python exception.
 */
#define Raise(type,msg) {PyErr_SetString(type,msg);}

/**
 * Sets a Python exception and goto tag
 */
#define raiseException_gotoTag(tag, type, msg) \
{PyErr_SetString(type, msg); goto tag;}

/**
 * Sets a Python exception and return NULL
 */
#define raiseException_returnNULL(type, msg) \
{PyErr_SetString(type, msg); return NULL;}

/**
 * Error object for reporting errors to the Python interpreter
 */
static PyObject *ErrorObject;


/**
 * Checks which object type an input IO payload is
 * @param[in] RaveIO_t object
 * @returns Python integer
 */
static PyObject* _hello_func(PyObject* self, PyObject* args) {
  PyObject* object = NULL;
  PyRaveIO* pyrio = NULL;
  int retcode = Rave_ObjectType_UNDEFINED;

  if (!PyArg_ParseTuple(args, "O", &object)) {
    return NULL;
  }

  if (PyRaveIO_Check(object)) {
    pyrio = (PyRaveIO*)object;
  } else {
    raiseException_returnNULL(PyExc_AttributeError, 
			      "Hello check requires RaveIO object as input");
  }

  retcode = hello(pyrio->raveio);
  return PyInt_FromLong((long)retcode);
}


static struct PyMethodDef _hello_functions[] =
{
  { "hello", (PyCFunction) _hello_func, METH_VARARGS },
  { NULL, NULL }
};

/**
 * Initialize the _hello module
 */
PyMODINIT_FUNC init_hello(void)
{
  PyObject* m;
  m = Py_InitModule("_hello", _hello_functions);
  ErrorObject = PyString_FromString("_hello.error");

  if (ErrorObject == NULL || PyDict_SetItemString(PyModule_GetDict(m),
                                                  "error", ErrorObject) != 0) {
    Py_FatalError("Can't define _hello.error");
  }
  import_pyraveio();
  import_array(); /*To make sure we access numpy*/
  PYRAVE_DEBUG_INITIALIZE;
}

/*@} End of Module setup */
