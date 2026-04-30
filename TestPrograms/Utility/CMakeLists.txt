cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestUtils)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

file(GLOB_RECURSE sources source/*.c)

TP_add_interface_subdirectory(Types)

add_library(TeaPacket_TestUtils ${sources})
target_include_directories(TeaPacket_TestUtils PUBLIC include)
target_link_libraries(TeaPacket_TestUtils TeaPacket_Types_Base)

set_target_properties(TeaPacket_TestUtils PROPERTIES C_STANDARD 90)