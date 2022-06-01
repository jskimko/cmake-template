add_executable(${PROJECT_NAME}-bin
  main.cc
)

set_target_properties(${PROJECT_NAME}-bin
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME}-bin
  PRIVATE
    ${PROJECT_NAME}-lib
)

install(TARGETS ${PROJECT_NAME}-bin)
