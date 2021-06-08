# Create INTERFACE libraries
add_library(test INTERFACE)

# Target the sources that are to be included in this library
target_sources(test INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/i2c_test.c
)

# Add include files
target_include_directories(test INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Target other library dependencies
target_link_libraries(test INTERFACE
        pico_stdlib
        hardware_i2c
)