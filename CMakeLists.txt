cmake_minimum_required(VERSION 3.16)

project(Plotteron VERSION 0.1.0)

include(FetchContent) 
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/mahilab/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

find_library(LIBSERIALPORT_LIBRARIES serialport)
find_path(LIBSERIALPORT_INCLUDE_DIR libserialport.h)
include_directories(${LIBSERIALPORT_INCLUDE_DIR})

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(plotteron ${SOURCES} ${HEADERS})
target_link_libraries(plotteron mahi::gui ${LIBSERIALPORT_LIBRARIES})
