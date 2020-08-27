cmake_minimum_required (VERSION 3.1)
PROJECT(helloqt)

set(CMAKE_CXX_STANDARD 11)

# export QT5_INSTALL_PATH=Qt5.12.0/5.12.0/gcc_64
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_INSTALL_PATH})

# Enable Qt Support
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 依赖Qt的库
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Qml REQUIRED)

message(STATUS "Qt5Core_INCLUDE_DIRS: " ${Qt5Core_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECT_NAME} helloqt.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Network)

include_directories(hellowidget.h)
ADD_EXECUTABLE(hellowidget hellowidget.cpp main.cpp )
target_link_libraries(hellowidget Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Network)

ADD_EXECUTABLE(test_tcp_client test_tcp_client.cpp tcp_client.cpp )
target_link_libraries(test_tcp_client Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Network)

ADD_EXECUTABLE(test_tcp_server test_tcp_server.cpp tcp_server.cpp )
target_link_libraries(test_tcp_server Qt5::Core Qt5::Widgets Qt5::OpenGL Qt5::Network)