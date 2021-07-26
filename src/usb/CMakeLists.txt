# Create INTERFACE libraries
add_library(usb INTERFACE)

# Target the sources that are to be included in this library
target_sources(usb INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/usb_descriptors.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_msc.c
        ${CMAKE_CURRENT_LIST_DIR}/freertos_hook.c
        ${CMAKE_CURRENT_LIST_DIR}/usb_helper.c
)

# Add include files
target_include_directories(usb INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Target other library dependencies
target_link_libraries(usb INTERFACE
        pico_stdlib
        tinyusb_device 
        tinyusb_board
        FreeRTOS
        cmsis_core
)

