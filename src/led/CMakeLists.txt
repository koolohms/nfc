# Create INTERFACE libraries
add_library(led INTERFACE)

# Target the sources that are to be included in this library
target_sources(led INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/led.c
)

# Add include files
target_include_directories(led INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Target other library dependencies
target_link_libraries(led INTERFACE
        pico_stdlib
)