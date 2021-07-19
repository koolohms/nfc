add_executable(main
        main.c
        )
        
target_include_directories(main PRIVATE ./)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(main PRIVATE
        pico_stdlib 
        hardware_i2c 
        usb
        tinyusb_device 
        tinyusb_board
        led
        test
        nfcc
        pico_time
        pico_mem_ops
        drivers
        FreeRTOS
        cmsis_core
        )

# Add FreeRTOS library
add_library(FreeRTOS STATIC
        freertos/croutine.c
        freertos/event_groups.c
        freertos/list.c
        freertos/queue.c
        freertos/stream_buffer.c
        freertos/tasks.c
        freertos/timers.c
        freertos/portable/GCC/ARM_CM0/port.c
        freertos/portable/MemMang/heap_4.c
)
target_include_directories(FreeRTOS PUBLIC 
        freertos/include
        freertos/portable/GCC/ARM_CM0
)
target_link_libraries(FreeRTOS PUBLIC
        pico
        pico_stdlib 
        hardware_i2c 
        usb
        tinyusb_device 
        tinyusb_board
        led
        test
        nfcc
        pico_time
        pico_mem_ops
        drivers
        cmsis_core
)


# Declare global defines
target_compile_definitions(main PRIVATE P2P_SUPPORT)

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

add_subdirectory(drivers)
add_subdirectory(usb)
add_subdirectory(led)
add_subdirectory(test)
add_subdirectory(nfcc)
