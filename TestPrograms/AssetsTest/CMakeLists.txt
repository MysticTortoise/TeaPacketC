cmake_minimum_required(VERSION 3.28)
project(TeaPacket_TestPrograms_Assets)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")
include("${TEAPACKET_ROOT}/Subtools/AssetMixer/Functions.CMake")

add_executable(TeaPacket_TestPrograms_Assets main.c)
TP_add_bundle(${TEAPACKET_PLATFORM} TeaPacket_TestPrograms_Assets)
TP_add_interface_subdirectory(Bundled)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../Utility" TP_TestUtility)

target_link_libraries(TeaPacket_TestPrograms_Assets TeaPacket_Bundle TeaPacket_Bundled_Helper TeaPacket_TestUtils)


TP_AM_BuildAssets(
        TARGET TeaPacket_TestPrograms_Assets
        SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/"
)
set_target_properties(TeaPacket_TestPrograms_Assets PROPERTIES C_STANDARD 90)