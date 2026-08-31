cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_BMP)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Subtools/AssetMixer/Functions.CMake")

TP_add_extension_subdirectory(Formats/Image/BMP)

add_executable(TeaPacket_TestPrograms_BMP main.c)

TP_add_bundle(${TEAPACKET_PLATFORM})
set(TP_Bundle_Windows_InputLib WinMessage)
TP_build_bundle(${TEAPACKET_PLATFORM})


target_link_libraries(TeaPacket_TestPrograms_BMP PUBLIC TeaPacket_Extensions_Formats_Image_BMP)
TP_link_bundle(TeaPacket_TestPrograms_BMP ${TEAPACKET_PLATFORM})

TP_AM_BuildAssets(
        TARGET TeaPacket_TestPrograms_BMP
        SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/"
        PASSES ${TP_ASSET_MIXER_PASSES}
)
set_target_properties(TeaPacket_TestPrograms_BMP PROPERTIES C_STANDARD 90)