# Create INTERFACE libraries
add_library(drivers INTERFACE)

# Target the sources that are to be included in this library
target_sources(drivers INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/tool.c
)

# Add include files
target_include_directories(drivers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# Target other library dependencies
target_link_libraries(drivers INTERFACE
        pico_stdlib
        pico_time
        hardware_irq    
)