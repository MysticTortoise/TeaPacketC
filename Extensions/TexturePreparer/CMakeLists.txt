cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Extension_TexturePreparer)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
set(CMAKE_CXX_STANDARD 20)

TP_add_interface_subdirectory(Graphics)

file(GLOB_RECURSE sources source/*.c*)
add_library(TeaPacket_Extension_TexturePreparer STATIC ${sources})

target_include_directories(TeaPacket_Extension_TexturePreparer PUBLIC include)
target_include_directories(TeaPacket_Extension_TexturePreparer PRIVATE source)
target_link_libraries(TeaPacket_Extension_TexturePreparer
        TeaPacket_Graphics_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")