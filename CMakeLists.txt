cmake_minimum_required(VERSION 3.11)

set(PLOTTERON_VERSION "0.1.0")
project(Plotteron VERSION ${PLOTTERON_VERSION})

message(STATUS "Plotteron version ${PLOTTERON_VERSION}")

configure_file(src/config.hpp.in config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent) 

# mahi-gui
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/oxullo/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

# libserialport
FetchContent_Declare(libserialport GIT_REPOSITORY https://github.com/oxullo/libserialport)
FetchContent_MakeAvailable(libserialport)

# Plotteron
file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(plotteron ${SOURCES} ${HEADERS})
target_link_libraries(plotteron mahi::gui libserialport)
