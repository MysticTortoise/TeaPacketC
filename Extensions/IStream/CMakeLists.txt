cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Extensions_IStream)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Assets)
TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Endianness)


file(GLOB_RECURSE sources source/*.c)
add_library(TeaPacket_Extensions_IStream ${sources})
target_include_directories(TeaPacket_Extensions_IStream PUBLIC include)
target_link_libraries(TeaPacket_Extensions_IStream PUBLIC TeaPacket_Assets_Base TeaPacket_MacroUtils_Base
        TeaPacket_Endianness_Base)