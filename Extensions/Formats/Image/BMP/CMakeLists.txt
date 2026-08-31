cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Extensions_Formats_Image_BMP C)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(GraphicsCommon)
TP_add_interface_subdirectory(Assets)
TP_add_interface_subdirectory(Memory)

TP_add_interface_subdirectory(Logging)

TP_add_extension_subdirectory(IStream)
TP_add_extension_subdirectory(Image/Conversions)

file(GLOB_RECURSE sources source/*.c)
add_library(TeaPacket_Extensions_Formats_Image_BMP ${sources})
target_include_directories(TeaPacket_Extensions_Formats_Image_BMP PUBLIC include)

TP_add_impl_subdirectory(Assets CPPSTDFile)

target_link_libraries(TeaPacket_Extensions_Formats_Image_BMP PUBLIC
         TeaPacket_GraphicsCommon_Base TeaPacket_Assets_Base TeaPacket_Memory_Base
        TeaPacket_Logging_Base

         TeaPacket_Extensions_IStream TeaPacket_Extensions_Image_Conversions)

set_target_properties(TeaPacket_Extensions_Formats_Image_BMP PROPERTIES C_STANDARD 99)