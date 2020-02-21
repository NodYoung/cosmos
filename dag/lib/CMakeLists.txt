project(dag_lib)

file (GLOB _INCS "lib/*.h")
file (GLOB _SRCS "lib/*.cpp")

add_library(${PROJECT_NAME} STATIC ${_SRCS} ${_INCS})
target_link_libraries(${PROJECT_NAME} ${DAG_LINKER_LIBS})