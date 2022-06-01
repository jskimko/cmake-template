add_library(${PROJECT_NAME}-lib
  example.cc
)

set_target_properties(${PROJECT_NAME}-lib
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
    EXPORT_NAME ${PROJECT_NAME}
    PUBLIC_HEADER example.hh
)

target_include_directories(${PROJECT_NAME}-lib
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

install(TARGETS ${PROJECT_NAME}-lib 
  EXPORT ${PROJECT_NAME}-export
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_file(projectConfig.cmake.in ${PROJECT_NAME}Config.cmake @ONLY)
install(FILES 
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)


