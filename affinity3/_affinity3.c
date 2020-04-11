#include "Python.h"
#include <sched.h>

PyDoc_STRVAR(_affinity3__doc__, "Linux Processor Affinity\n");

static PyObject *
get_process_affinity_mask(PyObject *self, PyObject *args)
{
    unsigned long cur_mask;
    unsigned int len = sizeof(cur_mask);
    pid_t pid;

    if (!PyArg_ParseTuple(args, "i:get_process_affinity_mask", &pid))
        return NULL;

    if (sched_getaffinity(pid, len, (cpu_set_t *)&cur_mask) < 0) {
        PyErr_SetFromErrno(PyExc_ValueError);
        return NULL;
    }

    return Py_BuildValue("l", cur_mask);
}

static PyObject *
set_process_affinity_mask(PyObject *self, PyObject *args)
{
    unsigned long new_mask;
    unsigned long cur_mask;
    unsigned int len = sizeof(new_mask);
    pid_t pid;

    if (!PyArg_ParseTuple(args, "il:set_process_affinity_mask", &pid, &new_mask))
        return NULL;

    if (sched_getaffinity(pid, len, (cpu_set_t *)&cur_mask) < 0) {
        PyErr_SetFromErrno(PyExc_ValueError);
        return NULL;
    }

    if (sched_setaffinity(pid, len, (cpu_set_t *)&new_mask)) {
        PyErr_SetFromErrno(PyExc_ValueError);
        return NULL;
    }

    return Py_BuildValue("l", cur_mask);
}

static PyMethodDef methods[] = {
    {"get_process_affinity_mask", get_process_affinity_mask, METH_VARARGS,
        "get_process_affinity_mask(pid) ->\n\
Get the process affinity mask of 'pid'.\n\n\
You can get the affinity mask of any process running\n\
in the system, even if you are not the process owner."},
    {"set_process_affinity_mask", set_process_affinity_mask, METH_VARARGS,
        "set_process_affinity_mask(pid, affinity_mask) ->\n\
Set the process affinity mask of 'pid' to 'affinity_mask'\n\
and return the previous affinity mask.\n\n\
If the PID is set to zero, the PID of the current task is used.\n\n\
Note: you must be 'root' or the owner of 'pid' in\n\
order to be able to call this."},
    {NULL, NULL, 0, NULL},
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "_affinity3",       /* name of module */
    _affinity3__doc__,  /* module documentation, may be NULL */
    -1,                 /* size of per-interpreter state of the module,
                        or -1 if the module keeps state in global variables. */
    methods
};

PyMODINIT_FUNC
PyInit_affinity3(void)
{
    return PyModule_Create(&module);
}

