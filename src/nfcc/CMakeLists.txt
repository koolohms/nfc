# Create INTERFACE libraries
add_library(nfc INTERFACE)

# Target the sources that are to be included in this library
target_sources(nfc INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/NxpNci.c
        ${CMAKE_CURRENT_LIST_DIR}/P2P_NDEF.c
        ${CMAKE_CURRENT_LIST_DIR}/tml.c
        ${CMAKE_CURRENT_LIST_DIR}/ndef_helper.c
        ${CMAKE_CURRENT_LIST_DIR}/nfc_task.c

)

# Add include files
target_include_directories(nfc INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Target other library dependencies
target_link_libraries(nfc INTERFACE
        pico_stdlib
        pico_time
        pico_mem_ops
)