cmake_minimum_required (VERSION 3.1)
PROJECT(boost_ref)
# define project name, define <projectname>_BINARY_DIR and <projectname>_SOURCE_DIR implicitly
set(CMAKE_CXX_FLAGS "-std=c++11 -g -fPIC")

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

add_executable(callback1 callback1.cpp)
add_executable(callback2 callback2.cpp)