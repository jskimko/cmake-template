add_executable(proj-bin
    main.cc)

set_target_properties(proj-bin
    PROPERTIES
        OUTPUT_NAME proj
)

target_link_libraries(proj-bin
    example)
