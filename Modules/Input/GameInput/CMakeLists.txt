cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Input_GameInput)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

include("${TEAPACKET_ROOT}/Generators/EnumMapGen/Functions.CMake")

set(CMAKE_CXX_STANDARD 20)

TP_add_interface_subdirectory(Input)
TP_add_interface_subdirectory(Types)
TP_add_interface_subdirectory(Logging)
TP_add_impl_subdirectory(Window Windows)

add_subdirectory_no_overwrite(TeaPacket_MacroUtils_WinSpecific "${TEAPACKET_ROOT}/Modules/MacroUtils/WindowsSpecific" WindowsSpecificMacros)

file(GLOB_RECURSE sources source/*.c*)

add_library(TeaPacket_Input_GameInput STATIC ${sources})

TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/VirtualKey.gmap" TeaPacket_Input_GameInput)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/MouseButton.gmap" TeaPacket_Input_GameInput)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/ControllerType.gmap" TeaPacket_Input_GameInput)
TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/GamepadButton.gmap" TeaPacket_Input_GameInput)

TP_EnumMapGen("${CMAKE_CURRENT_SOURCE_DIR}/generators/GamepadButton.gmap" TeaPacket_Input_GameInput)

TP_run_python_script(TeaPacket_Input_GameInput "${CMAKE_CURRENT_SOURCE_DIR}/setup/setup.py")
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/setup/gameinput_dir.gen") # not very good but idk how to make it better
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/setup/gameinput_dir.gen" GAMEINPUT_DIR)
else()
    message("WARNING: DUE TO JANK, YOU WILL NEED TO COMPILE, LET IT ERROR, THEN RELOAD CMAKE, THEN EVERYTHING WILL WORK FINE. I KNOW IT SUCKS BUT IM TOO LAZY TO FIX IT YET.")
endif ()


target_include_directories(TeaPacket_Input_GameInput PRIVATE source)
target_include_directories(TeaPacket_Input_GameInput PUBLIC include 
"${GAMEINPUT_DIR}/include")
target_link_libraries(TeaPacket_Input_GameInput TeaPacket_Input_Base 
        TeaPacket_Logging_Base TeaPacket_MacroUtils_WinSpecific
        TeaPacket_Window_Windows
        TeaPacket_Types_Base
        "${GAMEINPUT_DIR}/lib/GameInput.lib"
)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")