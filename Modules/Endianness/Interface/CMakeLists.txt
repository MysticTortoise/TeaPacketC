cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Endianness_Base)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
TP_add_interface_subdirectory(MacroUtils)
TP_add_interface_subdirectory(Types)


if(NOT DEFINED TP_DEBUG)
    set(TP_DEBUG 0)
endif()

file(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c")

add_library(TeaPacket_Endianness_Base ${src})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(TeaPacket_Endianness_Base TeaPacket_MacroUtils_Base TeaPacket_Types_Base)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")