# Create INTERFACE libraries
add_library(board INTERFACE)

# Target the sources that are to be included in this library
target_sources(board INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/board.c
)

# Add include files
target_include_directories(board INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Target other library dependencies
target_link_libraries(board INTERFACE
        pico_stdlib
)