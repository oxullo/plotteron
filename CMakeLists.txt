cmake_minimum_required(VERSION 3.17)

project(Plotteron VERSION 0.1.0)

include(FetchContent) 
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/mahilab/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

file(GLOB SOURCES src/*.cpp)

add_executable(plotteron ${SOURCES})
target_link_libraries(plotteron mahi::gui)
