PROJECT(chapter16)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
# define project name, define <projectname>_BINARY_DIR and <projectname>_SOURCE_DIR implicitly
#set(CMAKE_CXX_FLAGS "-std=c++11 -g -fPIC")
#set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

#MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
#MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})

find_package(Boost REQUIRED COMPONENTS system thread)
include_directories(include ${Boost_INCLUDE_DIRS})

file (GLOB _INCS "*.h")
file (GLOB _SRCS "*.cpp")
add_executable(test_server Message.h RWHandler.h Server.h test_server.cpp)
add_executable(test_client Message.h RWHandler.h Connector.h test_client.cpp)

target_link_libraries(test_server ${Boost_LIBRARIES} glog)
target_link_libraries(test_client ${Boost_LIBRARIES} glog)

