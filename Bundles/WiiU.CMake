TP_add_impl_subdirectory(Assets WUHBContent)
TP_add_interface_subdirectory(Endianness)
TP_add_impl_subdirectory(Graphics GX2)
TP_add_impl_subdirectory(Input WiiU)
TP_add_impl_subdirectory(Logging WHBLogUDP)
TP_add_interface_subdirectory(MacroUtils)
TP_add_impl_subdirectory(Memory CMem)
TP_add_impl_subdirectory(Random STDRandom)
TP_add_impl_subdirectory(System WiiU)
TP_add_impl_subdirectory(Time CoreinitU)
TP_add_interface_subdirectory(Types)

add_library(TeaPacket_Bundle INTERFACE)
target_link_libraries(TeaPacket_Bundle INTERFACE
        TeaPacket_Assets_WUHBContent
        TeaPacket_Endianness_Base
        TeaPacket_Graphics_GX2
        TeaPacket_Input_WiiU
        TeaPacket_Logging_WHBLogUDP
        TeaPacket_MacroUtils_Base
        TeaPacket_Memory_CMem
        TeaPacket_Random_STDRandom
        TeaPacket_System_WiiU
        TeaPacket_Time_CoreinitU
        TeaPacket_Types_Base
)

if(DEFINED TEAPACKET_PLATFORM)
    if(TEAPACKET_PLATFORM STREQUAL "WiiU" AND DEFINED TEAPACKET_BUNDLE_TARGET)
        message("TEAPACKET PROFILE: CREATING RPX AUTOMATICALLY")
        wut_create_rpx(${TEAPACKET_BUNDLE_TARGET})
        if(COMMAND TP_AM_BuildAssets)
            set(TP_WUHB_ASSET_PATH "--content=assets")
        endif()
        add_custom_command(
                TARGET ${TEAPACKET_BUNDLE_TARGET}
                POST_BUILD
                COMMENT "TEAPACKET PROFILE: MAKING WUHB"
                COMMAND wuhbtool
                "${TEAPACKET_BUNDLE_TARGET}.rpx"
                "${TEAPACKET_BUNDLE_TARGET}.wuhb"
                ${TP_WUHB_ASSET_PATH}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    else()
        message("UHHH WHAT")
    endif()
endif ()