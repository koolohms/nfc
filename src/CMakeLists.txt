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
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(main)

add_subdirectory(usb)
