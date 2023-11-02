################################
# Library
################################

add_library(${PROJECT_NAME_LOWER}-lib)
add_library(${PROJECT_NAME_LOWER}::${PROJECT_NAME_LOWER} ALIAS ${PROJECT_NAME_LOWER}-lib)

set_target_properties(${PROJECT_NAME_LOWER}-lib
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME_LOWER}
    EXPORT_NAME ${PROJECT_NAME_LOWER}
)

target_include_directories(${PROJECT_NAME_LOWER}-lib
  PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(${PROJECT_NAME_LOWER}-lib 
  PUBLIC 
    cxxopts::cxxopts
  PRIVATE
    spdlog::spdlog
)

cmake_language(CALL ${PROJECT_NAME_LOWER}_set_public_headers
  TARGET ${PROJECT_NAME_LOWER}-lib
  MAIN_HEADER "${PROJECT_NAME_LOWER}.hh"
  BASE_DIR ".."
)

################################
# Subdirectories
################################

add_subdirectory(util)

################################
# Install
################################

install(TARGETS ${PROJECT_NAME_LOWER}-lib 
  EXPORT ${PROJECT_NAME_LOWER}-export
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  FILE_SET HEADERS
)

install(EXPORT ${PROJECT_NAME_LOWER}-export
  FILE ${PROJECT_NAME_LOWER}-targets.cmake
  NAMESPACE ${PROJECT_NAME_LOWER}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME_LOWER}"
)

