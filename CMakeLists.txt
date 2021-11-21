cmake_minimum_required(VERSION 3.11)

project(Plotteron VERSION 0.1.0)

include(FetchContent) 
include(ExternalProject)

# mahi-gui
FetchContent_Declare(mahi-gui GIT_REPOSITORY https://github.com/oxullo/mahi-gui.git) 
FetchContent_MakeAvailable(mahi-gui)

# libserialport
ExternalProject_Add(libserialport
    PREFIX _deps/libserialport
    GIT_REPOSITORY https://github.com/sigrokproject/libserialport
    UPDATE_DISCONNECTED true  # need this to avoid constant rebuild
    CONFIGURE_HANDLED_BY_BUILD ON  # avoid constant reconfigure
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=<INSTALL_DIR>
    )

ExternalProject_Get_Property(libserialport SOURCE_DIR)

ExternalProject_Add_Step(libserialport
  bootstrap
  COMMAND ./autogen.sh
  DEPENDEES download
  DEPENDERS configure
  WORKING_DIRECTORY ${SOURCE_DIR}
  )

set(LIBSERIALPORT_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/_deps/libserialport/include)
set(LIBSERIALPORT_LIB ${CMAKE_CURRENT_BINARY_DIR}/_deps/libserialport/lib/libserialport.a)
include_directories(${LIBSERIALPORT_INCLUDE_DIR})

# Plotteron

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS src/*.hpp)

add_executable(plotteron ${SOURCES} ${HEADERS})
target_link_libraries(plotteron mahi::gui ${LIBSERIALPORT_LIB})
