#include <pybind11/pybind11.h>
#include <example/example.hh>

namespace py = pybind11;

namespace example {

PYBIND11_MODULE(_example, m) {
  m.doc() = "example c++ module";

  py::class_<Settings>(m, "Settings")
    .def("getInt", &Settings::get<int>)
    .def("getString", &Settings::get<std::string>)
    .def("setInt", py::overload_cast<std::string const &, int>(&Settings::set))
    .def("setString", py::overload_cast<std::string const &, std::string>(&Settings::set))
  ;

  auto m_log = m.def_submodule("log", "ccsat log module");
  py::enum_<log::Level>(m_log, "Level")
    .value("NONE", log::Level::NONE)
    .value("INFO", log::Level::INFO)
    .value("DEBUG", log::Level::DEBUG)
    .value("TRACE", log::Level::TRACE)
    .export_values()
  ;

}

} // namespace example
