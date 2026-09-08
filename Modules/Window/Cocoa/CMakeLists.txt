cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Window_Cocoa OBJC)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Window)
TP_add_interface_subdirectory(Memory)

find_library(COCOA_FRAMEWORK Cocoa REQUIRED)

file(GLOB_RECURSE sources source/*.m*)

add_library(TeaPacket_Window_Cocoa STATIC ${sources})
target_include_directories(TeaPacket_Window_Cocoa PRIVATE source)
target_include_directories(TeaPacket_Window_Cocoa PUBLIC include)
target_link_libraries(TeaPacket_Window_Cocoa PUBLIC TeaPacket_Window_Base TeaPacket_Memory_Base
    ${COCOA_FRAMEWORK})

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")