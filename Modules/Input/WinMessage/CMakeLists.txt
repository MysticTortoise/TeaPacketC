cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Input_WinMessage)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

TP_add_interface_subdirectory(Input)
TP_add_interface_subdirectory(Types)
TP_add_interface_subdirectory(Logging)

TP_add_impl_subdirectory(Window Windows)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Input_WinMessage STATIC ${sources})

target_include_directories(TeaPacket_Input_WinMessage PRIVATE source)
target_include_directories(TeaPacket_Input_WinMessage PUBLIC include)
target_link_libraries(TeaPacket_Input_WinMessage TeaPacket_Input_Base
        TeaPacket_Logging_Base
        TeaPacket_Types_Base
        TeaPacket_Window_Windows
)

get_filename_component(INPUT_MODULE_DIR ../ ABSOLUTE)
TP_EnumMapGen("${INPUT_MODULE_DIR}/GameInput/generators/VirtualKey.gmap" TeaPacket_Input_WinMessage)


set_target_properties(TeaPacket_Input_WinMessage PROPERTIES CXX_STANDARD 17)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")