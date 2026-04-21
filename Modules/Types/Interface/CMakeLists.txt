cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Types_Base)

TP_add_interface_subdirectory(MacroUtils)

include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_Types_Base INTERFACE TeaPacket_MacroUtils_Base)