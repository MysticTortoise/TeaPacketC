cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Bundled_Helper)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

#file(GLOB_RECURSE sources source/*.c)

add_custom_command(
        OUTPUT "include/TeaPacket/Bundled/Init.h" "include/TeaPacket/Bundled/DeInit.h"
        DEPENDS generators/InitModuleList.txt
        COMMENT "Generating Init Headers..."
        COMMAND python3 "${CMAKE_CURRENT_SOURCE_DIR}/generators/init.py"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/generators/"
        VERBATIM
)

add_library(TeaPacket_Bundled_Helper INTERFACE "include/TeaPacket/Bundled/Init.h" "include/TeaPacket/Bundled/DeInit.h")
target_include_directories(TeaPacket_Bundled_Helper INTERFACE include)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")