cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Logging_CPP)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_cpp_subdirectory(Types)

set(TEAPACKET_WRAPPER_CPP_MODULE Logging)
include("${TEAPACKET_ROOT}/CMakeCommons/CPPWrapperCommon.CMake")

target_link_libraries(TeaPacket_Logging_CPP INTERFACE TeaPacket_Types_CPP)