cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Types_CPP)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Memory)

set(TEAPACKET_WRAPPER_CPP_MODULE Types)
include("${TEAPACKET_ROOT}/CMakeCommons/CPPWrapperCommon.CMake")

target_link_libraries(TeaPacket_Types_CPP INTERFACE TeaPacket_Memory_Base)