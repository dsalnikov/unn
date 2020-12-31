#define PY_SSIZE_T_CLEAN
#include <Python.h>


#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
/* #include <numpy/ndarraytypes.h> */
#include <numpy/arrayobject.h>

#include <iostream>

static PyObject*
py_conv2d(PyObject* self, PyObject* args)
{
    PyArrayObject* inp;
    PyArrayObject* kernel;

    /* Parse arguments from Python:
       "O!" - PyArrayType (numpy) object */
    if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &inp, &PyArray_Type, &kernel))
        return NULL;


    int ndim = PyArray_NDIM(inp);
    npy_intp* inpShape = PyArray_SHAPE(inp);
    npy_intp* kernelShape = PyArray_SHAPE(inp);

    /*  Compute output shape: */
    npy_intp* outpShape;
    //TODO: compute shape

    /*  Create output array: */
    PyObject* outp = PyArray_ZEROS(ndim, outpShape, NPY_FLOAT, 0);

    float* pInp = (float *)PyArray_DATA(inp);
    float* pKernel = (float *)PyArray_DATA(kernel);
    float* pOutp = (float *)PyArray_DATA((PyArrayObject*)outp); //TODO: check this pointer if ok

    /* Call conv2d */
    /* conv2d(pInp, pKernel, pOutp, ); */


    return Py_BuildValue("N", outp);
}




PyObject* foo(PyObject *self, PyObject *args)
{
    /* PyObject *prm0; */
    /* PyObject *prm1; */

    /* if (PyArg_UnpackTuple(args, "ref", 1, 2, &prm0, &prm1)) */
    /* { */
    /*     double a = PyFloat_AsDouble(prm0); */
    /*     double b = PyFloat_AsDouble(prm1); */
    /*     return PyFloat_FromDouble(a + b); */
    /* } */
    npy_intp dims[1] = {5,};

    PyObject *arr = PyArray_ZEROS(1, dims, NPY_DOUBLE, 1);

    return Py_BuildValue("N", arr);
}

/* Errors */
static PyObject *MultiplyError;

/*
 * Enter point from Python
 */
static PyObject*
py_multiply(PyObject* self, PyObject* args)
{
    PyArrayObject *in_arr=NULL, *in_arr_second=NULL, *out_arr=NULL;
    int nd = 0, nd_second = 0;

    /* Parse arguments from Python:
       "O!" - check type of object
       &in_arr  - to variable in_arr
     */
    if (!PyArg_ParseTuple(args, "O!O!", &PyArray_Type, &in_arr, &PyArray_Type, &in_arr_second))
        return NULL;

    /* Get number of dimensions
     */
    nd = PyArray_NDIM(in_arr);
    nd_second = PyArray_NDIM(in_arr_second);

    /* Get length of array from shape
       [0] - length
     */
    int length = (int)PyArray_SHAPE(in_arr)[0];
    int length_second = (int)PyArray_SHAPE(in_arr_second)[0];

    /* Error with different sizes
     */
    if (length != length_second) {
        PyErr_SetString(MultiplyError, "Arrays have different sizes");
        return NULL;
    }
    /* Error with wrong ndim
     */
    if (nd != 1 || nd != nd_second) {
        PyErr_SetString(MultiplyError, "Arrays must have 1 dimension");
        return NULL;
    }

    /* Create array with zeros
     */
    out_arr = (PyArrayObject *) PyArray_ZEROS(nd, PyArray_SHAPE(in_arr), NPY_DOUBLE, 0);

    /* Get pointer to the first elements of arrays
     */
    double *item = (double *)PyArray_DATA(in_arr);
    double *item_second = (double *)PyArray_DATA(in_arr_second);
    double *item_out = (double *)PyArray_DATA(out_arr);

    double *end = (item + length);
    double *end_second = (item_second + length_second);
    for (int i = 0; item != end && item_second != end_second; item++, item_second++, i++) {
        item_out[i] = (*item) * (*item_second);
    }

    /* Return new array without increase reference count:
     * O - increase reference count
     * N - not increase reference count
     */
    return Py_BuildValue("N", out_arr);
}

static PyMethodDef unn_methods[] = {
    { "foo", (PyCFunction)foo, METH_VARARGS, NULL},
    { "multiply", py_multiply, METH_VARARGS, "Multiply two numpy arrays."},

    { "conv2d", py_conv2d, METH_VARARGS, "Compute 2d convolution"},
   
    // Terminate the array with an object containing nulls.
    { NULL, NULL, 0, NULL }
};

static struct PyModuleDef unn_module = {
    PyModuleDef_HEAD_INIT,
    "unn",                        // Module name to use with Python import statements
    "Provides simple C implementation of nn functions",  // Module description
    0,
    unn_methods                   // Structure that defines the methods of the module
};

PyMODINIT_FUNC PyInit_unn() {
    /* return PyModule_Create(&superfastcode_module); */
    PyObject *m;
    m = PyModule_Create(&unn_module);
    if (!m) {
        return NULL;
    }

    /* Import NUMPY settings
     */
    import_array();

    /* Init errors */
    MultiplyError = PyErr_NewException("multiply.error", NULL, NULL);
    Py_INCREF(MultiplyError); /* Increment reference count for object */
    PyModule_AddObject(m, "error", MultiplyError);

    return m;
}
