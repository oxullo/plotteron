cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
project(cdc_spewer C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(cdc_spewer main.c)

# enable usb output, disable uart output
pico_enable_stdio_usb(cdc_spewer 1)
pico_enable_stdio_uart(cdc_spewer 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(cdc_spewer)

# Pull in our pico_stdlib which aggregates commonly used features
target_link_libraries(cdc_spewer pico_stdlib)

