cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Input_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Generators/EnumGenerator/Functions.CMake")

TP_add_interface_subdirectory(Types)
include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_Input_Base INTERFACE TeaPacket_Types_Base)

TP_EnumGenerator(
        "${CMAKE_CURRENT_SOURCE_DIR}/generators/InputButton.enum"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/TeaPacket/Input/Button.h"
        TeaPacket_Input_Base)

TP_EnumGenerator(
        "${CMAKE_CURRENT_SOURCE_DIR}/generators/InputAxis.enum"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/TeaPacket/Input/Axis.h"
        TeaPacket_Input_Base)

TP_EnumGenerator(
        "${CMAKE_CURRENT_SOURCE_DIR}/generators/ControllerType.enum"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/TeaPacket/Input/ControllerType.h"
        TeaPacket_Input_Base)