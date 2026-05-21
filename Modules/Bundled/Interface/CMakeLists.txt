cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Bundled_Base)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Types)

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/include/TeaPacket/Bundled/Init.h" "${CMAKE_CURRENT_SOURCE_DIR}/include/TeaPacket/Bundled/DeInit.h"
        DEPENDS generators/InitModuleList.txt
        COMMENT "Generating Init Headers..."
        COMMAND python "${CMAKE_CURRENT_SOURCE_DIR}/generators/init.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/generators/"
        VERBATIM
)

add_library(TeaPacket_Bundled_Base INTERFACE "include/TeaPacket/Bundled/Init.h" "include/TeaPacket/Bundled/DeInit.h")
target_include_directories(TeaPacket_Bundled_Base INTERFACE include)
target_link_libraries(TeaPacket_Bundled_Base INTERFACE
        TeaPacket_Types_Base TeaPacket_MacroUtils_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")