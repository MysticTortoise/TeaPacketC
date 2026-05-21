cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Input)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Bundled)

add_executable(TeaPacket_TestPrograms_Input main.c)
TP_add_bundle(${TEAPACKET_PLATFORM} TeaPacket_TestPrograms_Input)
target_link_libraries(TeaPacket_TestPrograms_Input TeaPacket_Bundle TeaPacket_Bundled_Base)

set_target_properties(TeaPacket_TestPrograms_Input PROPERTIES C_STANDARD 90)