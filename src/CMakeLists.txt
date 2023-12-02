################################
# Library
################################

add_library(example-lib)
add_library(example::example ALIAS example-lib)

set_target_properties(example-lib
  PROPERTIES
    OUTPUT_NAME example
    EXPORT_NAME example
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
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>" # config.hh
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(example-lib 
  PUBLIC
    fmt::fmt
)

example_set_public_headers(
  TARGET example-lib
  MAIN_HEADER "example.hh"
)

################################
# Subdirectories
################################

add_subdirectory(util)

################################
# Install
################################

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.hh.in" 
               "${CMAKE_CURRENT_BINARY_DIR}/config.hh")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/config.hh"
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/example")

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

