cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Logging_STDIO)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Logging)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Logging_STDIO STATIC ${sources})
target_include_directories(TeaPacket_Logging_STDIO PRIVATE source)
target_link_libraries(TeaPacket_Logging_STDIO TeaPacket_Logging_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")