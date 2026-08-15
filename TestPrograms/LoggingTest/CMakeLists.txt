cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Logging)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Logging)

TP_add_bundle(${TEAPACKET_PLATFORM})
TP_build_bundle(${TEAPACKET_PLATFORM})

add_executable(TeaPacket_TestPrograms_Logging main.c)
target_link_libraries(TeaPacket_TestPrograms_Logging PRIVATE TeaPacket_Logging_Base)
TP_link_bundle(TeaPacket_TestPrograms_Logging ${TEAPACKET_PLATFORM})
set_target_properties(TeaPacket_TestPrograms_Logging PROPERTIES C_STANDARD 90)