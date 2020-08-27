cmake_minimum_required(VERSION 2.8)
project(constructor_misc)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -fno-elide-constructors")
set(CMAKE_CXX_FLAGS_RELEASE  "-std=c++11 -O3 -fopenmp -pthread")

SET(EXAMPLES copy_vs_assign)
FOREACH (example ${EXAMPLES})
    ADD_EXECUTABLE(${example} ${example}.cpp)
    TARGET_LINK_LIBRARIES(${example} glog)
ENDFOREACH ()

