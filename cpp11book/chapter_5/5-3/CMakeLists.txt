PROJECT(5-3)

FILE (GLOB HDRS "${CMAKE_CURRENT_SOURCE_DIR}/5-3/*.h")
FILE (GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/5-3/*.cpp")

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/5-3)
ADD_EXECUTABLE(5-3 ${SRCS})
