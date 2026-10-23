cmake_minimum_required(VERSION 3.28)
project(TeaPacket_GraphicsGS_OpenGL C)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(GraphicsGS)
TP_add_interface_subdirectory(MacroUtils)
TP_add_impl_subdirectory(Logging STDIO)

TP_add_impl_subdirectory(GraphicsGS Helper)

#TP_add_extension_subdirectory(TexturePreparer)

file(GLOB_RECURSE sources source/*.c)

add_library(TeaPacket_GraphicsGS_OpenGL STATIC ${sources})

add_subdirectory(platform)

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

include(generators/CMakeLists.txt)

target_include_directories(TeaPacket_GraphicsGS_OpenGL PRIVATE source)
target_include_directories(TeaPacket_GraphicsGS_OpenGL PUBLIC include)
target_link_libraries(TeaPacket_GraphicsGS_OpenGL TeaPacket_GraphicsGS_Base
        TP_GfxGS_GL_Platform
        TeaPacket_GraphicsGS_Helper
        TeaPacket_MacroUtils_Base
        TeaPacket_Logging_STDIO
        )

set(TP_ASSET_MIXER_PASSES "${TP_ASSET_MIXER_PASSES};${CMAKE_CURRENT_SOURCE_DIR}/GLShaderMixer/pass/glsmixer_shader.py" CACHE INTERNAL "" FORCE)

if("${TP_GfxGS_GL_SpecsVer}" STREQUAL "GL")
    set(version_def TP_GfxGS_GL_SpecsVer_GL)
elseif("${TP_GfxGS_GL_SpecsVer}" STREQUAL "ES")
    set(version_def TP_GfxGS_GL_SpecsVer_ES)
endif ()

target_compile_definitions(TeaPacket_GraphicsGS_OpenGL PUBLIC
        "TP_GfxGS_GL_MajorVer=${TP_GfxGS_GL_MajorVer}"
        "TP_GfxGS_GL_MinorVer=${TP_GfxGS_GL_MinorVer}"
        "${version_def}"
)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")