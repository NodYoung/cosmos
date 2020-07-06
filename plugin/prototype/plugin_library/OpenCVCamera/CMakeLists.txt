

project(OpenCVCamera)

file(GLOB ${PROJECT_NAME}_files src/*)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_files})

target_link_libraries(${PROJECT_NAME} plugin_prototype)


