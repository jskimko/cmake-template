add_executable(${PROJECT_NAME_LOWER}-bin
  main.cc
)

set_target_properties(${PROJECT_NAME_LOWER}-bin
  PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME_LOWER}
)

target_link_libraries(${PROJECT_NAME_LOWER}-bin
  PRIVATE
    ${PROJECT_NAME_LOWER}::${PROJECT_NAME_LOWER}
)

install(TARGETS ${PROJECT_NAME_LOWER}-bin)
