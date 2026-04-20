cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Graphics_GX2)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

set(CMAKE_CXX_STANDARD 20)

TP_add_interface_subdirectory(Graphics)
TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Math)
TP_add_interface_subdirectory(Logging)

TP_add_extension_subdirectory(TexturePreparer)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Graphics_GX2 STATIC ${sources})

TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureFormat.gmap" TeaPacket_Graphics_GX2)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureWrap.gmap" TeaPacket_Graphics_GX2)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureFilter.gmap" TeaPacket_Graphics_GX2)

target_include_directories(TeaPacket_Graphics_GX2 PRIVATE source)
target_include_directories(TeaPacket_Graphics_GX2 PUBLIC include)
target_link_libraries(TeaPacket_Graphics_GX2 TeaPacket_Graphics_Base TeaPacket_Logging_Base
        TeaPacket_Extension_TexturePreparer)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")