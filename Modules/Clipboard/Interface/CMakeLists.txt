cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Clipboard_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Generators/EnumGenerator/Functions.CMake")

TP_add_interface_subdirectory(Types)
TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(GraphicsGS)

include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_Clipboard_Base INTERFACE TeaPacket_Types_Base
        TeaPacket_MacroUtils_Base TeaPacket_GraphicsGS_Base)

TP_EnumGenerator(
        "${PROJECT_SOURCE_DIR}/generators/ClipboardContentsType.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Clipboard/ContentsType.h"
        TeaPacket_Clipboard_Base)