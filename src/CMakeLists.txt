################################
# Library
################################

add_library(example-lib)
add_library(example::example ALIAS example-lib)

set_target_properties(example-lib
  PROPERTIES
    OUTPUT_NAME example
    EXPORT_NAME example

    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}"
    POSITION_INDEPENDENT_CODE ${ENABLE_PYBIND11}

    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_compile_features(example-lib
  PUBLIC
    cxx_std_20
)

if(EXAMPLE_MAIN_PROJECT)
  target_compile_options(example-lib 
    PUBLIC
    -Wall -Wextra -pedantic $<$<BOOL:${ENABLE_WERROR}>:-Werror>
  )
endif()

target_include_directories(example-lib
  PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>" # config.hh
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(example-lib 
  PUBLIC
    $<$<BOOL:${ENABLE_MPI}>:MPI::MPI_CXX>
    $<$<BOOL:${ENABLE_PYBIND11}>:pybind11::pybind11>
    range-v3::range-v3
    fmt::fmt
)

example_set_public_headers(
  TARGET example-lib
  MAIN_HEADER "example.hh"
)

target_sources(example-lib
  PRIVATE
    Settings.cc
)

################################
# Subdirectories
################################

add_subdirectory(util)

if(ENABLE_PYBIND11)
  add_subdirectory(python)
endif()

################################
# Install
################################

set(EXAMPLE_PYTHON_PURELIB_DIR "${PROJECT_BINARY_DIR}/${PYTHON_PURELIB_DIR}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hh.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/config.hh")

set(EXAMPLE_PYTHON_PURELIB_DIR "${CMAKE_INSTALL_PREFIX}/${PYTHON_PURELIB_DIR}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hh.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/config-install.hh")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/config-install.hh"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/example"
  RENAME "config.hh")

install(TARGETS example-lib 
  EXPORT example-export
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  FILE_SET HEADERS
)

install(EXPORT example-export
  FILE example-targets.cmake
  NAMESPACE example::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/example"
)

