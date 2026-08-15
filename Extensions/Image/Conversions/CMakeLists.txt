cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Extensions_Image_Conversions)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Graphics)
TP_add_interface_subdirectory(Memory)

file(GLOB_RECURSE sources source/*.c)
add_library(TeaPacket_Extensions_Image_Conversions ${sources})
target_include_directories(TeaPacket_Extensions_Image_Conversions PUBLIC include)

target_link_libraries(TeaPacket_Extensions_Image_Conversions PUBLIC 
        TeaPacket_Graphics_Base TeaPacket_Memory_Base)