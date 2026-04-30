cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Graphics_Helper)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Graphics)
TP_add_interface_subdirectory(Types)

set(CMAKE_C_STANDARD 90)

file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/source/*.c*")

add_library(TeaPacket_Graphics_Helper STATIC ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")
target_link_libraries(TeaPacket_Graphics_Helper PUBLIC TeaPacket_Types_Base TeaPacket_Graphics_Base)