cmake_minimum_required(VERSION 3.6)
# 默认编译标准
set(CMAKE_CXX_STANDARD 11)

# 编译器命令行参数
if (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /source-charset:utf-8")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
else ()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif ()

# Qt编译扩展
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} $ENV{QT5_INSTALL_PATH})   # Qt5
# 依赖Qt的库
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Qml REQUIRED)


file(GLOB ${PROJECT_NAME}_files src/*)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_files})

# 依赖链接库
if (WIN32)
    target_link_libraries(${PROJECT_NAME}
            Ws2_32
            Qt5::Core
            Qt5::Widgets
            Qt5::OpenGL
            Qt5::Network
            ${OpenCV_LIBRARIES}
            ${Boost_LIBRARIES}
            ${extend_library_list})
else ()
    target_link_libraries(${PROJECT_NAME}
            rt
            Qt5::Core
            Qt5::Widgets
            Qt5::OpenGL
            Qt5::Network
            ${OpenCV_LIBRARIES}
            ${Boost_LIBRARIES}
            glog)
endif ()