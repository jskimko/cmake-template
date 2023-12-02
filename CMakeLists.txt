cmake_minimum_required(VERSION 3.23)
# 3.9 -> MPI::MPI_<lang> target
# 3.12 -> <PackageName>_ROOT
# 3.13 -> relative target_sources (CMP0076)
# 3.23 -> target_sources(FILE_SET)

################################
# Project
################################

project(example
        VERSION 0.1.0
        LANGUAGES CXX)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

################################
# Build configuration
################################

if(NOT DEFINED EXAMPLE_MAIN_PROJECT)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(EXAMPLE_MAIN_PROJECT ON)
  else()
    set(EXAMPLE_MAIN_PROJECT OFF)
  endif()
endif()

option(ENABLE_TESTS "Enable tests" ${EXAMPLE_MAIN_PROJECT})
option(ENABLE_WERROR "Set -Werror" OFF)

################################
# Project configuration
################################

option(ENABLE_MPI "Enable MPI" OFF)
option(ENABLE_PYBIND11 "Enable pybind11" OFF)

include(cmake/example-setup.cmake)

################################
# Subdirectories
################################

add_subdirectory(app)
add_subdirectory(example)

if(ENABLE_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()

