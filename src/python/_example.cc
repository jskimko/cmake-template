#include <pybind11/pybind11.h>
#include <example/example.hh>

PYBIND11_MODULE(_example, m) {
  m.doc() = "example c++ module";
}
