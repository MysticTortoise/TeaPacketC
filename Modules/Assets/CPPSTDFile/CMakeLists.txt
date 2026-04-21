cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Assets_CPPSTDFile)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Assets)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Assets_CPPSTDFile STATIC ${sources})
target_include_directories(TeaPacket_Assets_CPPSTDFile PRIVATE source)
#target_include_directories(TeaPacket_Assets_CPPSTDFile PUBLIC include)
target_link_libraries(TeaPacket_Assets_CPPSTDFile TeaPacket_Assets_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")