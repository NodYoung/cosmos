project(dag)
cmake_minimum_required(VERSION 3.5)

include(cmake/Utils.cmake)

# ---[ Dependencies
include(cmake/Dependencies.cmake)

file(GLOB proto_files proto/*.proto)
dag_protobuf_generate_cpp_py(${proto_gen_folder} proto_srcs proto_hdrs proto_python ${proto_files})

include_directories (${PROJECT_SOURCE_DIR})
add_subdirectory (apps)

#add_subdirectory (common)
#add_subdirectory (lib)
#add_subdirectory (onboard)
#
#add_executable (subnode_test test/subnode_test.cpp)
#target_link_libraries (subnode_test gtest gtest_main glog)
#add_test(NAME subnode_test COMMAND subnode_test)




