add_library(example
    example.cc
)

target_compile_features(example
    PUBLIC
        cxx_std_11
)

set_target_properties(example
    PROPERTIES 
        CXX_EXTENSIONS OFF
)

target_include_directories(example
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)
