cmake_minimum_required(VERSION 2.8)
project(opencv_misc)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "-std=c++11 -O3 -fopenmp -pthread")

# OpenCV
find_package(OpenCV 4.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
message(STATUS "${OpenCV_INCLUDE_DIRS}")
include_directories(${PROJECT_SOURCE_DIR})

SET(EXAMPLES opencv_yaml
        opencv_yaml1
        calibrate_hand_eye)
FOREACH (example ${EXAMPLES})
    ADD_EXECUTABLE(${example} ${example}.cpp)
    TARGET_LINK_LIBRARIES(${example} ${OpenCV_LIBS} glog)
ENDFOREACH ()

