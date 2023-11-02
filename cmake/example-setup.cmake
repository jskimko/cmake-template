################################
# Check config
################################

################################
# Other dependencies
################################

find_package(cxxopts REQUIRED)
find_package(spdlog REQUIRED)

################################
# Scoped variables
################################

set(${PROJECT_NAME_UPPER}_DEFAULT_VERBOSE_LEVEL ${DEFAULT_VERBOSE_LEVEL})

################################
# Generate config.hh
################################

configure_file("${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME_LOWER}/config.hh.in" 
               "${PROJECT_BINARY_DIR}/src/${PROJECT_NAME_LOWER}/config.hh")

install(FILES "${PROJECT_BINARY_DIR}/src/${PROJECT_NAME_LOWER}/config.hh"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME_LOWER}"
)

################################
# Generate cmake config files
################################

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME_LOWER}-config-version.cmake"
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  "${CMAKE_SOURCE_DIR}/cmake/${PROJECT_NAME_LOWER}-config.cmake.in"
  "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME_LOWER}-config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}"
)

install(FILES 
  "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME_LOWER}-config.cmake"
  "${CMAKE_BINARY_DIR}/cmake/${PROJECT_NAME_LOWER}-config-version.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}"
)

################################
# Functions
################################

function(${PROJECT_NAME_LOWER}_set_public_headers)
  set(_one_value_args "TARGET" "MAIN_HEADER" "BASE_DIR")
  cmake_parse_arguments(SET_PUBLIC_HEADERS "" "${_one_value_args}" "" ${ARGN})

  if(NOT TARGET "${SET_PUBLIC_HEADERS_TARGET}")
    message(FATAL_ERROR "nonexistent TARGET: ${SET_PUBLIC_HEADERS_TARGET}")
  endif()

  get_filename_component(_main_header "${SET_PUBLIC_HEADERS_MAIN_HEADER}" ABSOLUTE)
  if("${_main_header}" STREQUAL "" OR NOT EXISTS "${_main_header}")
    message(FATAL_ERROR "cannot find MAIN_HEADER: ${SET_PUBLIC_HEADERS_MAIN_HEADER}")
  endif()

  get_filename_component(_base_dir "${SET_PUBLIC_HEADERS_BASE_DIR}" ABSOLUTE)
  if("${_base_dir}" STREQUAL "" OR NOT EXISTS "${_base_dir}")
    message(FATAL_ERROR "cannot find BASE_DIR: ${SET_PUBLIC_HEADERS_BASE_DIR}")
  endif()

  set(_public_headers "${_main_header}")
  file(STRINGS "${_main_header}" _main_header_strings REGEX "#include")
  foreach(_string ${_main_header_strings})
    string(REGEX MATCH "^[ \t\r\n]*//" _comment ${_string})
    if(NOT "${_comment}" STREQUAL "")
      continue()
    endif()

    string(REGEX MATCH "[A-Za-z_/]*\.hh" _public_header ${_string})
    set(_public_header "${_base_dir}/${_public_header}")

    if(NOT EXISTS "${_public_header}")
      message(FATAL_ERROR "cannot find included header: ${_public_header}")
    endif()

    list(APPEND _public_headers "${_public_header}")
  endforeach()

  target_sources("${SET_PUBLIC_HEADERS_TARGET}"
    PUBLIC
      FILE_SET
        HEADERS
        BASE_DIRS "${_base_dir}"
        FILES ${_public_headers}
  )

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS "${_main_header}")
endfunction()
