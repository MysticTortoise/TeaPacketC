cmake_minimum_required(VERSION 3.28)
project(TeaPacket_Bundled_CPP)

include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")

file(GLOB_RECURSE incSources "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")

TP_add_interface_subdirectory(Bundled)

add_library(${PROJECT_NAME} INTERFACE ${incSources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(${PROJECT_NAME} INTERFACE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} INTERFACE TeaPacket_Bundled_Base)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")

if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
    target_compile_options(${PROJECT_NAME} INTERFACE "/Zc:__cplusplus")
endif()