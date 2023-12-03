set(_src "${CMAKE_CURRENT_SOURCE_DIR}/example")
set(_dest "${PROJECT_BINARY_DIR}/${PYTHON_PURELIB_DIR}/example")

pybind11_add_module(example-pyb _example.cc)

set_target_properties(example-pyb
  PROPERTIES
    OUTPUT_NAME _example
    LIBRARY_OUTPUT_DIRECTORY "${_dest}"
)

target_link_libraries(example-pyb
  PUBLIC
    example::example
)

add_custom_target(example-py ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${_src}" "${_dest}"
)

install(DIRECTORY "${_src}" DESTINATION "${PYTHON_PURELIB_DIR}")
install(TARGETS example-pyb LIBRARY DESTINATION "${PYTHON_PURELIB_DIR}/example")

unset(_src)
unset(_dest)
