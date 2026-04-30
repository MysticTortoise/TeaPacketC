cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Assets_WUHBContent)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Assets)
TP_add_interface_subdirectory(Memory)
TP_add_interface_subdirectory(Logging)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Assets_WUHBContent STATIC ${sources})
target_include_directories(TeaPacket_Assets_WUHBContent PRIVATE source)
#target_include_directories(TeaPacket_Assets_STDFile PUBLIC include)
target_link_libraries(TeaPacket_Assets_WUHBContent TeaPacket_Assets_Base
        TeaPacket_Memory_Base TeaPacket_Logging_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")