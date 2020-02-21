project(dag_onboard)

file (GLOB _INCS "*.h")
file (GLOB _SRCS "*.cpp")

add_library(${PROJECT_NAME} STATIC ${_SRCS} ${_INCS})
target_link_libraries(${PROJECT_NAME} ${DAG_LINKER_LIBS})
