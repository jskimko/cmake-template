#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <cstdio>
#include <cstdlib>

#include <example/config.hh>

#ifdef EXAMPLE_ENABLE_MPI
#include <mpi.h>
#define EXIT(rc) MPI_Abort(rc);
#else
#define EXIT(rc) std::exit(rc);
#endif

int main(int argc, char *argv[]) {

#ifdef EXAMPLE_ENABLE_MPI
  MPI_Init(&argc, &argv);
#endif
  
  // BEGIN https://docs.python.org/3.10/c-api/init_config.html
  PyStatus status;
  PyConfig config;

  auto exception = [&]() {
    PyConfig_Clear(&config);
    if (!PyStatus_IsExit(status)) {
      fprintf(stderr, "error: %s\n", status.err_msg);
    }
    EXIT(status.exitcode);
  };

  PyConfig_InitPythonConfig(&config);

  status = PyConfig_SetBytesArgv(&config, argc, argv);
  if (PyStatus_Exception(status)) { exception(); }

  status = PyConfig_Read(&config);
  if (PyStatus_Exception(status)) { exception(); }

  status = PyWideStringList_Insert(&config.module_search_paths, 0, 
                                   EXAMPLE_PYTHON_PURELIB_DIR);
  if (PyStatus_Exception(status)) { exception(); }

  status = Py_InitializeFromConfig(&config);
  if (PyStatus_Exception(status)) { exception(); }
  PyConfig_Clear(&config);

  int rc = Py_RunMain();
  if (rc != 0) { EXIT(rc); }
  // END https://docs.python.org/3.10/c-api/init_config.html

#ifdef EXAMPLE_ENABLE_MPI
  MPI_Finalize();
#endif

  return rc;
}

