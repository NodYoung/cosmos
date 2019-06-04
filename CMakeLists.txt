cmake_minimum_required (VERSION 3.1)
PROJECT(cosmos)
# define project name, define <projectname>_BINARY_DIR and <projectname>_SOURCE_DIR implicitly
set(CMAKE_CXX_FLAGS "-std=c++11 -g -fPIC")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

find_package(Boost REQUIRED COMPONENTS system thread filesystem)
include_directories(include ${Boost_INCLUDE_DIRS})

add_subdirectory(cpp11book)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
ADD_EXECUTABLE(Aspect Aspect_test.cpp)
ADD_EXECUTABLE(Boost_Filesystem boost_filesystem.cpp)
target_link_libraries(Boost_Filesystem ${Boost_LIBRARIES})