cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Graphics_CPP)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Generators/EnumGenerator/Functions.CMake")

TP_add_interface_cpp_subdirectory(Types)

set(TEAPACKET_WRAPPER_CPP_MODULE Graphics)
include("${TEAPACKET_ROOT}/CMakeCommons/CPPWrapperCommon.CMake")

target_link_libraries(TeaPacket_Graphics_CPP INTERFACE TeaPacket_Types_CPP)

include(Generators.CMake)