################################
# example python
################################

if(ENABLE_PYBIND11)
  add_executable(examplepy-bin examplepy.cc)

  set_target_properties(examplepy-bin
    PROPERTIES
      OUTPUT_NAME example
      RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
  )

  target_link_libraries(examplepy-bin PRIVATE example::example Python3::Python)
  install(TARGETS examplepy-bin)
endif()

################################
# example c++
################################

add_executable(examplecpp-bin examplecpp.cc)

set_target_properties(examplecpp-bin
  PROPERTIES
    OUTPUT_NAME examplecpp
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}"
)

target_link_libraries(examplecpp-bin PRIVATE example::example)
install(TARGETS examplecpp-bin)

