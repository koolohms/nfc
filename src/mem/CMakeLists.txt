# Create INTERFACE libraries
add_library(mem INTERFACE)

# Target the sources that are to be included in this library
target_sources(mem INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/mem_helper.c
)

# Add include files
target_include_directories(mem INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Target other library dependencies
target_link_libraries(mem INTERFACE
        pico_stdlib
        tinyusb_device 
        tinyusb_board
        FreeRTOS
        cmsis_core
)

