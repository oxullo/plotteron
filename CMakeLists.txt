cmake_minimum_required(VERSION 3.11)

project(Plotteron VERSION 0.1.0)

configure_file(src/config.hpp.in config.hpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent) 
include(ExternalProject)

# mahi-gui
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/oxullo/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

# libserialport
ExternalProject_Add(libserialport
    PREFIX _deps/libserialport
    GIT_REPOSITORY https://github.com/sigrokproject/libserialport
    GIT_TAG 6f9b03e597ea7200eb616a4e410add3dd1690cb1
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND <SOURCE_DIR>/autogen.sh && <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    BUILD_BYPRODUCTS ${INSTALL_DIR}/lib/libserialport.a
    )

ExternalProject_Get_Property(libserialport SOURCE_DIR)

set(LIBSERIALPORT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/libserialport/include)
set(LIBSERIALPORT_LIB ${CMAKE_CURRENT_BINARY_DIR}/_deps/libserialport/lib/libserialport.a)
include_directories(${LIBSERIALPORT_INCLUDE_DIR})

# Plotteron

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(plotteron ${SOURCES} ${HEADERS})
target_link_libraries(plotteron mahi::gui ${LIBSERIALPORT_LIB})
