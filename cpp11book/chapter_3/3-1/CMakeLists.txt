cmake_minimum_required (VERSION 3.1)
PROJECT(3-1)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

FILE (GLOB HDRS "${CMAKE_CURRENT_SOURCE_DIR}/3-1/*.h")
FILE (GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/3-1/*.cpp")

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/3-1)
ADD_EXECUTABLE(3-1 ${SRCS})
