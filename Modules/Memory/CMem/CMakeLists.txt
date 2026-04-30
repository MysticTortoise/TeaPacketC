cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Memory_CMem)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Memory)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Memory_CMem STATIC ${sources})
target_link_libraries(TeaPacket_Memory_CMem TeaPacket_Memory_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")

set_target_properties(TeaPacket_Memory_CMem PROPERTIES C_STANDARD 90)