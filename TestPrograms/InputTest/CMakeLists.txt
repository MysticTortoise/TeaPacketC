cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Input)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Bundled)

add_executable(TeaPacket_TestPrograms_Input main.c)

TP_add_bundle(${TEAPACKET_PLATFORM})

#set(TP_Bundle_Windows_InputLib WinMessage)

TP_build_bundle(${TEAPACKET_PLATFORM})
TP_link_bundle(TeaPacket_TestPrograms_Input ${TEAPACKET_PLATFORM})

set_target_properties(TeaPacket_TestPrograms_Input PROPERTIES C_STANDARD 90)