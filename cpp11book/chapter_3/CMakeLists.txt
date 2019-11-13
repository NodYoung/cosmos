cmake_minimum_required (VERSION 3.1)
PROJECT(chapter03)
# define project name, define <projectname>_BINARY_DIR and <projectname>_SOURCE_DIR implicitly
#set(CMAKE_CXX_FLAGS "-std=c++11 -g -fPIC")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
#MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

add_subdirectory(3-1)
add_subdirectory(3-2)
add_subdirectory(3-3)
add_subdirectory(3-4)
#add_subdirectory(3-15)
