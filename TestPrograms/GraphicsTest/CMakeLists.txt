cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Graphics)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Subtools/AssetMixer/Functions.CMake")

add_executable(TeaPacket_TestPrograms_Graphics source/main.c)
target_include_directories(TeaPacket_TestPrograms_Graphics PUBLIC source)
add_subdirectory(source)

TP_add_bundle(${TEAPACKET_PLATFORM})
TP_build_bundle(${TEAPACKET_PLATFORM})
TP_link_bundle(TeaPacket_TestPrograms_Graphics ${TEAPACKET_PLATFORM})

TP_AM_BuildAssets(
        TARGET TeaPacket_TestPrograms_Graphics 
        SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/" 
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/"
        PASSES ${TP_ASSET_MIXER_PASSES}
        )
set_target_properties(TeaPacket_TestPrograms_Graphics PROPERTIES C_STANDARD 99)

get_target_property(OUT TeaPacket_TestPrograms_Graphics LINK_LIBRARIES)
target_compile_definitions(TeaPacket_TestPrograms_Graphics PUBLIC GFXTESTS_ALLOWED=99 TP_DEBUG=${TP_DEBUG})