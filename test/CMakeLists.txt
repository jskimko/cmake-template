add_test(NAME "examplecpp-bin"
  COMMAND examplecpp-bin
)

if(ENABLE_PYBIND11)
  add_test(NAME "examplepy-bin"
    COMMAND examplepy-bin -c "from example import *"
  )
endif()

