cmake_minimum_required(VERSION 3.6)
project(plugin_prototype)
set(CMAKE_CXX_STANDARD 11)

set (CMAKE_BUILD_TYPE "Release")
message("Build Type: ${CMAKE_BUILD_TYPE}")

if (MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /source-charset:utf-8 /MP /wd4828")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8 /MP /wd4828")
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wno-deprecated-declarations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-deprecated-declarations")
endif ()

# OpenCV
find_package (OpenCV REQUIRED COMPONENTS core highgui imgproc video features2d imgcodecs calib3d)
include_directories (${OpenCV_INCLUDE_DIRS})
message (STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message (STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")

# glog
set(GLOG_INCLUDE_DIRS /usr/include)
set(GLOG_LIBRARIES glog)

# boost
find_package(Boost 1.58 COMPONENTS system regex timer filesystem REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})
message (STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message (STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

#QT5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_INSTALL_PATH})
message("CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}")
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Qml REQUIRED)

include_directories (${PROJECT_SOURCE_DIR})

add_subdirectory (framework)
add_subdirectory (plugin_library)
add_subdirectory (apps)
