cmake_minimum_required(VERSION 3.28)
project(TeaPacket_GraphicsGS_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Generators/EnumGenerator/Functions.CMake")

TP_add_interface_subdirectory(GraphicsCommon)
TP_add_interface_subdirectory(Types)
#TP_add_interface_subdirectory(Core)
TP_add_interface_subdirectory(Endianness)
TP_add_interface_subdirectory(MacroUtils)
include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_GraphicsGS_Base INTERFACE TeaPacket_Types_Base TeaPacket_Endianness_Base
        TeaPacket_MacroUtils_Base TeaPacket_GraphicsCommon_Base)

include(generators/CMakeLists.txt)