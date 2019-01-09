cmake_minimum_required (VERSION 3.1)
PROJECT(pthread)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

#FILE (GLOB HDRS "*.h")
#FILE (GLOB SRCS "*.cpp")

#include_directories (${CMAKE_CURRENT_SOURCE_DIR}/5-1)
ADD_EXECUTABLE(pthread_01 pthread_1.cpp)
ADD_EXECUTABLE(pthread_02 pthread_2.cpp)
ADD_EXECUTABLE(pthread_03 pthread_3.cpp)
