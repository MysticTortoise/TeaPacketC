cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Time_CoreinitU)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Time)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Time_CoreinitU STATIC ${sources})
target_include_directories(TeaPacket_Time_CoreinitU PRIVATE source)
#target_include_directories(TeaPacket_Time_STDChrono PUBLIC include)
target_link_libraries(TeaPacket_Time_CoreinitU TeaPacket_Time_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")