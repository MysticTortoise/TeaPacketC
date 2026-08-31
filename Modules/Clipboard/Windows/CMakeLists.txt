cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Clipboard_Windows)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

TP_add_interface_subdirectory(Clipboard)

TP_add_extension_subdirectory(Formats/Image/BMP)

TP_add_impl_subdirectory(Window Windows)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Clipboard_Windows STATIC ${sources})

target_include_directories(TeaPacket_Clipboard_Windows PRIVATE source)
#target_include_directories(TeaPacket_Input_WinMessage PUBLIC include)
target_link_libraries(TeaPacket_Clipboard_Windows TeaPacket_Clipboard_Base
        TeaPacket_Window_Windows TeaPacket_Extensions_Formats_Image_BMP
)
set_target_properties(TeaPacket_Clipboard_Windows PROPERTIES CXX_STANDARD 17)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")