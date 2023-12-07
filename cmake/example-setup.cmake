################################
# Apply configuration
################################

if(ENABLE_MPI)
  find_package(MPI REQUIRED)
endif()

if(ENABLE_PYBIND11)
  find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
  find_package(pybind11 REQUIRED)

  if(NOT PYTHON_PURELIB_DIR)
    execute_process(
      COMMAND "${Python3_EXECUTABLE}" -c "if True:
        import sysconfig; p = sysconfig.get_path('purelib', vars={'base': ''})
        print(p.lstrip('/'), end='')"
      OUTPUT_VARIABLE PYTHON_PURELIB_DIR
    )
  endif()
endif()

################################
# Required dependencies
################################

find_package(range-v3 REQUIRED)
find_package(fmt REQUIRED)

################################
# C++ config macros
################################

set(EXAMPLE_ENABLE_MPI ${ENABLE_MPI})
set(EXAMPLE_ENABLE_PYBIND11 ${ENABLE_PYBIND11})
set(EXAMPLE_ENABLE_LOGGING ${ENABLE_LOGGING})
set(EXAMPLE_DEFAULT_VERBOSITY ${DEFAULT_VERBOSITY})

################################
# Generate cmake config files
################################

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/cmake/example-config-version.cmake"
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/example-config.cmake.in"
  "${PROJECT_BINARY_DIR}/cmake/example-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/example"
)

install(FILES 
  "${PROJECT_BINARY_DIR}/cmake/example-config.cmake"
  "${PROJECT_BINARY_DIR}/cmake/example-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/example"
)

################################
# Functions
################################

function(example_set_public_headers)
  set(_one_value_args "TARGET" "MAIN_HEADER")
  cmake_parse_arguments(SET_PUBLIC_HEADERS "" "${_one_value_args}" "" ${ARGN})

  if(NOT TARGET "${SET_PUBLIC_HEADERS_TARGET}")
    message(FATAL_ERROR "nonexistent TARGET: ${SET_PUBLIC_HEADERS_TARGET}")
  endif()

  set(_main_header "${CMAKE_CURRENT_SOURCE_DIR}/${SET_PUBLIC_HEADERS_MAIN_HEADER}")
  if("${_main_header}" STREQUAL "" OR NOT EXISTS "${_main_header}")
    message(FATAL_ERROR "cannot find MAIN_HEADER: ${_main_header}")
  endif()

  set(_public_headers "${_main_header}")
  file(STRINGS "${_main_header}" _main_header_strings REGEX "#include")
  foreach(_string ${_main_header_strings})
    string(REGEX MATCH "^[ \t\r\n]*//" _comment ${_string})
    if(NOT "${_comment}" STREQUAL "")
      continue()
    endif()

    string(REGEX MATCH "example/[A-Za-z_/]*\.hh" _public_header ${_string})
    if("${_public_header}" STREQUAL "example/config.hh")
      continue() # handled separately
    endif()

    set(_public_header "${PROJECT_SOURCE_DIR}/${_public_header}")
    if(NOT EXISTS "${_public_header}")
      message(FATAL_ERROR "cannot find included header: ${_public_header}")
    endif()

    list(APPEND _public_headers "${_public_header}")
  endforeach()

  target_sources("${SET_PUBLIC_HEADERS_TARGET}"
    PUBLIC
      FILE_SET
        HEADERS
        BASE_DIRS "${PROJECT_SOURCE_DIR}"
        FILES ${_public_headers}
  )

  set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_main_header}")
endfunction()
