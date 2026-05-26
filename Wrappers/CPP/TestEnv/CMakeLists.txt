cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_CPP)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Subtools/AssetMixer/Functions.CMake")


add_executable(TeaPacket_TestPrograms_CPP main.cpp)
TP_add_bundle(${TEAPACKET_PLATFORM})
TP_build_bundle(${TEAPACKET_PLATFORM})
TP_link_bundle(TeaPacket_TestPrograms_CPP ${TEAPACKET_PLATFORM})

TP_add_interface_cpp_subdirectory(Assets)
TP_add_interface_cpp_subdirectory(Bundled)
TP_add_interface_cpp_subdirectory(Types)
TP_add_interface_cpp_subdirectory(Endianness)
TP_add_interface_cpp_subdirectory(Graphics)
TP_add_interface_cpp_subdirectory(Input)
TP_add_interface_cpp_subdirectory(Logging)
TP_add_interface_cpp_subdirectory(Random)
TP_add_interface_cpp_subdirectory(System)
TP_add_interface_cpp_subdirectory(Time)
TP_add_interface_cpp_subdirectory(Window)


#TP_add_extension_subdirectory(STBImageLoader)
target_link_libraries(TeaPacket_TestPrograms_CPP PRIVATE
        TeaPacket_Assets_CPP TeaPacket_Types_CPP
        TeaPacket_Bundled_CPP
        TeaPacket_Endianness_CPP
        TeaPacket_Graphics_CPP
        TeaPacket_Input_CPP
        TeaPacket_Logging_CPP
        TeaPacket_Random_CPP
        TeaPacket_System_CPP
        TeaPacket_Time_CPP
        TeaPacket_Window_CPP)

#TP_AM_BuildAssets(
#        TARGET TeaPacket_TestPrograms_Graphics
#        SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
#        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/"
#        PASSES ${TP_ASSET_MIXER_PASSES}
#)
set_target_properties(TeaPacket_TestPrograms_CPP PROPERTIES CXX_STANDARD 20)
set_target_properties(TeaPacket_TestPrograms_CPP PROPERTIES CXX_STANDARD_REQUIRED ON)