cmake_minimum_required(VERSION 3.2)

project(expert_sistem)

# gtk4
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

# yaml-cpp
find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIRS})

add_definitions(-std=c++11)
set(SRCS main.cpp)
add_executable(expert ${SRCS})
target_link_libraries(expert ${YAML_CPP_LIBRARIES} ${GTK4_LIBRARIES})

#g++ `pkg-config --cflags gtk4` main.cpp `pkg-config --libs gtk4`
