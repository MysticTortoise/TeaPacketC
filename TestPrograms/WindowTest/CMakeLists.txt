cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Window)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

add_executable(TeaPacket_TestPrograms_Window main.c)

TP_add_bundle(${TEAPACKET_PLATFORM})
TP_build_bundle(${TEAPACKET_PLATFORM})
TP_link_bundle(TeaPacket_TestPrograms_Window ${TEAPACKET_PLATFORM})

set_target_properties(TeaPacket_TestPrograms_Window PROPERTIES C_STANDARD 90)