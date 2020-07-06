cmake_minimum_required(VERSION 2.8)

project(Tutorial_create_robot)

# 默认编译标准
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_INSTALL_PATH})   # Qt5
include_directories(/usr/local/include/cobotsys)

# Enable Qt Support
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)

message("Qt5Widgets_INCLUDE_DIRS: ${Qt5Widgets_INCLUDE_DIRS}")
message("Qt5OpenGL_INCLUDE_DIRS: ${Qt5OpenGL_INCLUDE_DIRS}")
message("Qt5Network_INCLUDE_DIRS: ${Qt5Network_INCLUDE_DIRS}")
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

function(tutorial_app main_file)
    get_filename_component(f_base ${main_file} NAME_WE)
    add_executable(tutorial_${f_base} ${main_file})
    target_link_libraries(tutorial_${f_base} plugin_prototype)
endfunction()

tutorial_app(create_opencv_camera.cpp)

