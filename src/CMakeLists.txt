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

target_compile_features(${PROJECT_NAME_LOWER}-lib
  PUBLIC
    cxx_std_20
)

if(${PROJECT_NAME_UPPER}_MAIN_PROJECT)
  target_compile_options(${PROJECT_NAME_LOWER}-lib 
    PUBLIC
    -Wall -Wextra -pedantic $<$<BOOL:${ENABLE_WERROR}>:-Werror>
  )
endif()

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/include")
file(CREATE_LINK "${CMAKE_CURRENT_SOURCE_DIR}" 
                 "${PROJECT_BINARY_DIR}/include/example" SYMBOLIC)

target_include_directories(${PROJECT_NAME_LOWER}-lib
  PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>"
    "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(${PROJECT_NAME_LOWER}-lib 
  PUBLIC
    fmt::fmt
)

cmake_language(CALL ${PROJECT_NAME_LOWER}_set_public_headers
  TARGET ${PROJECT_NAME_LOWER}-lib
  MAIN_HEADER "${PROJECT_NAME_LOWER}.hh"
  BASE_DIR "${PROJECT_BINARY_DIR}/include"
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

