# Create INTERFACE libraries
add_library(gpio INTERFACE)

# Target the sources that are to be included in this library
target_sources(gpio INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/gpio.c
)

# Add include files
target_include_directories(gpio INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Target other library dependencies
target_link_libraries(gpio INTERFACE
        pico_stdlib
        hardware_irq
)