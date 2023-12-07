#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <example/example.hh>
#include <cstdlib>
#include <cstring>

#if EXAMPLE_ENABLE_MPI
#include <mpi.h>
#define EXIT(rc) do { MPI_Finalize(); std::exit(rc); } while (0)
#define LOG(level, ...) do { if (rank == 0) log::level(__VA_ARGS__); } while (0)
#else
#define EXIT(rc) std::exit(rc);
#define LOG(level, ...) do { log::level(__VA_ARGS__); } while (0)
#endif

#define LOG_INFO(...) LOG(info, __VA_ARGS__)
#define LOG_ERROR(...) LOG(error, __VA_ARGS__)

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
  using namespace example;

#if EXAMPLE_ENABLE_MPI
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif

  auto usage = [&argv]() {
    return fmt::format(
      "{0} - convenience program to enable easy `import {0}`\n"
      "usage: {0} [PYTHON_ARGS...] script.py [SCRIPT_ARGS...]",
      EXAMPLE_PROJECT_NAME);
  };

  for (int i=0; i<argc; i++) {
    if (std::strcmp(argv[i], "-h") == 0 || std::strcmp(argv[i], "--help") == 0) {
      LOG_INFO("{}\n", usage());
      EXIT(0);
    }
  }
  
  // BEGIN https://docs.python.org/3.10/c-api/init_config.html
  PyStatus status;
  PyConfig config;

  auto exception = [&]() {
    PyConfig_Clear(&config);
    if (!PyStatus_IsExit(status)) {
      LOG_ERROR("pyinit error: {}\n", status.err_msg);
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

#if EXAMPLE_ENABLE_MPI
  MPI_Finalize();
#endif

  return rc;
}

