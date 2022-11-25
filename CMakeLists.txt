set(PROJECT  p_bus)
cmake_minimum_required(VERSION 3.12)
set(PICO_BOARD pico)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(${PROJECT} C CXX)
pico_sdk_init()

add_executable(${PROJECT} ${PROJECT}.c)

pico_generate_pio_header(${PROJECT} ${CMAKE_CURRENT_LIST_DIR}/p_bus.pio)
target_sources(${PROJECT} PRIVATE
        ${PROJECT}.c
        )

target_include_directories(${PROJECT} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT} PRIVATE
     pico_stdlib
     hardware_pio
)

pico_add_extra_outputs(${PROJECT})
pico_enable_stdio_usb(${PROJECT} 1)
pico_enable_stdio_uart(${PROJECT} 0)

