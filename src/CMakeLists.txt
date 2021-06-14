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
