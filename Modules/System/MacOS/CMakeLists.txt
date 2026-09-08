cmake_minimum_required(VERSION 3.28)
project(TeaPacket_System_MacOS C OBJC)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(System)
TP_add_impl_subdirectory(Window Cocoa)

find_library(COCOA_FRAMEWORK Cocoa REQUIRED)

file(GLOB_RECURSE sources source/*.m*)

add_library(TeaPacket_System_MacOS STATIC ${sources})
#target_include_directories(TeaPacket_System_MacOS PRIVATE source)
#target_include_directories(TeaPacket_System_MacOS PUBLIC include)
target_link_libraries(TeaPacket_System_MacOS PUBLIC TeaPacket_System_Base)
target_link_libraries(TeaPacket_System_MacOS PRIVATE ${COCOA_FRAMEWORK})

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")