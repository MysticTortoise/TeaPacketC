cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Input_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Generators/EnumGenerator/Functions.CMake")

TP_add_interface_subdirectory(Types)
include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_Input_Base INTERFACE TeaPacket_Types_Base)

# SOMEONE PLEASE FIGURE OUT WHY ADD_SUBDIRECTORY WONT WORK HERE
include(generators/CMakeLists.txt)