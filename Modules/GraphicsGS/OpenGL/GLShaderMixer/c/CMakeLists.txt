cmake_minimum_required(VERSION 3.28)
project(GLShaderMixer C CXX)

if(NOT DEFINED TEAPACKET_ROOT)
    set(TEAPACKET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../")
endif ()
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

add_subdirectory(lib)
add_subdirectory(cli)