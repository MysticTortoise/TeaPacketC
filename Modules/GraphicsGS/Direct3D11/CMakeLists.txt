cmake_minimum_required(VERSION 3.28)
project(TeaPacket_GraphicsGS_Direct3D11)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

set(CMAKE_CXX_STANDARD 20)


TP_add_interface_subdirectory(GraphicsGS)
TP_add_interface_subdirectory(MacroUtils)
#TP_add_interface_subdirectory(Math)
TP_add_impl_subdirectory(Window Windows)
TP_add_impl_subdirectory(Logging STDIO)

TP_add_impl_subdirectory(GraphicsGS Helper)

#TP_add_extension_subdirectory(TexturePreparer)


file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_GraphicsGS_Direct3D11 STATIC ${sources})

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureFormat.gmap" TeaPacket_GraphicsGS_Direct3D11)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureFilter.gmap" TeaPacket_GraphicsGS_Direct3D11)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/TextureWrap.gmap" TeaPacket_GraphicsGS_Direct3D11)

target_include_directories(TeaPacket_GraphicsGS_Direct3D11 PRIVATE source)
target_include_directories(TeaPacket_GraphicsGS_Direct3D11 PUBLIC include)
target_link_libraries(TeaPacket_GraphicsGS_Direct3D11 TeaPacket_GraphicsGS_Base TeaPacket_GraphicsGS_Helper
        TeaPacket_Window_Windows
        d3d11.lib D3DCompiler.lib
        TeaPacket_MacroUtils_Base
        TeaPacket_Logging_STDIO
        )

set(TP_ASSET_MIXER_PASSES "${TP_ASSET_MIXER_PASSES};${CMAKE_CURRENT_SOURCE_DIR}/AssetMixer/Passes/hlsl_shader.py" CACHE INTERNAL "" FORCE)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")