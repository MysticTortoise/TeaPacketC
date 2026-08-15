cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Endianness_Base)

TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Types)

include("${TEAPACKET_ROOT}/CMakeCommons/InterfaceCommon.CMake")
target_link_libraries(TeaPacket_Endianness_Base INTERFACE TeaPacket_MacroUtils_Base TeaPacket_Types_Base)

if(CMAKE_C_BYTE_ORDER STREQUAL "BIG_ENDIAN")
    target_compile_definitions(TeaPacket_Endianness_Base INTERFACE TP_ENDIAN_NATIVE=TP_ENDIAN_BIG)
elseif(CMAKE_C_BYTE_ORDER STREQUAL "LITTLE_ENDIAN")
    target_compile_definitions(TeaPacket_Endianness_Base INTERFACE TP_ENDIAN_NATIVE=TP_ENDIAN_LITTLE)
endif()
