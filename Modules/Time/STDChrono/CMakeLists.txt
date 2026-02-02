cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Time_STDChrono)

set(CMAKE_CXX_STANDARD 20)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Time)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Time_STDChrono STATIC ${sources})
target_include_directories(TeaPacket_Time_STDChrono PRIVATE source)
#target_include_directories(TeaPacket_Time_STDChrono PUBLIC include)
target_link_libraries(TeaPacket_Time_STDChrono TeaPacket_Time_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")