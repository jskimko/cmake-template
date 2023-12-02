pybind11_add_module(example-pyb
  _example.cc
)

set_target_properties(example-pyb
  PROPERTIES
    OUTPUT_NAME _example
)

target_link_libraries(example-pyb
  PUBLIC
    example::example
)
