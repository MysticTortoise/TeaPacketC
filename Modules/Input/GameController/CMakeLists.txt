cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Input_GameController)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

TP_add_interface_subdirectory(Input)
TP_add_interface_subdirectory(Memory)
TP_add_interface_subdirectory(Time)
TP_add_interface_subdirectory(Types)
TP_add_interface_subdirectory(Logging)

TP_add_impl_subdirectory(Window Cocoa)

file(GLOB_RECURSE sources source/*.m)

add_library(TeaPacket_Input_GameController STATIC ${sources})

target_include_directories(TeaPacket_Input_GameController PRIVATE source)
target_include_directories(TeaPacket_Input_GameController PUBLIC include)
target_link_libraries(TeaPacket_Input_GameController PUBLIC TeaPacket_Input_Base
        TeaPacket_Logging_Base
        TeaPacket_Types_Base
        TeaPacket_Time_Base

        TeaPacket_Window_Cocoa
)

find_library(GAMECONTROLLER_FRAMEWORK GameController REQUIRED)
target_link_libraries(TeaPacket_Input_GameController PRIVATE ${GAMECONTROLLER_FRAMEWORK})

include(generators/CMakeLists.txt)

TP_ModuleImplEnd(Input)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")