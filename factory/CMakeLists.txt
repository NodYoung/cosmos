cmake_minimum_required(VERSION 3.5)
project(factory)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build Type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -fPIC -Wno-deprecated-declarations")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories (${PROJECT_SOURCE_DIR})

# glog
list(APPEND FACTORY_LIBS glog)

file (GLOB HDRS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file (GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRCS})
target_link_libraries(${PROJECT_NAME} ${FACTORY_LIBS})