cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Time_QuartzCore)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

TP_add_interface_subdirectory(Time)


add_library(TeaPacket_Time_QuartzCore STATIC time.m)
target_link_libraries(TeaPacket_Time_QuartzCore PUBLIC TeaPacket_Time_Base)

find_library(QUARTZCORE_LIB QuartzCore REQUIRED)
target_link_libraries(TeaPacket_Time_QuartzCore PRIVATE ${QUARTZCORE_LIB})

TP_ModuleImplEnd(Time)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")