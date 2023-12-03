#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <example/config.hh>

#ifdef EXAMPLE_ENABLE_MPI
#include <mpi.h>
#define EXIT(rc) MPI_Abort(MPI_COMM_WORLD, rc);
#else
#define EXIT(rc) std::exit(rc);
#endif

extern "C" {
// BEGIN Python/getversion.c
const char* Py_GetVersion(void) {
  static char version[256];
  PyOS_snprintf(version, sizeof(version), "%.80s (%.80s %.80s) %.80s", 
      PY_VERSION, EXAMPLE_PROJECT_NAME, EXAMPLE_VERSION, Py_GetCompiler());
  return version;
}
// END Python/getversion.c
}

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
      fprintf(stderr, "pyinit error: %s\n", status.err_msg);
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

