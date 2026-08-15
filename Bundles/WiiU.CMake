set(TP_Bundle_WiiU_AssetsLib     CPPSTDFile     PARENT_SCOPE)
set(TP_Bundle_WiiU_GraphicsLib   GX2            PARENT_SCOPE)
set(TP_Bundle_WiiU_InputLib      WiiU           PARENT_SCOPE)
set(TP_Bundle_WiiU_LoggingLib    WHBLogUDP      PARENT_SCOPE)
set(TP_Bundle_WiiU_MemoryLib     CMem           PARENT_SCOPE)
set(TP_Bundle_WiiU_RandomLib     STDRandom      PARENT_SCOPE)
set(TP_Bundle_WiiU_SystemLib     WiiU           PARENT_SCOPE)
set(TP_Bundle_WiiU_TimeLib       CoreinitU      PARENT_SCOPE)

if(NOT COMMAND TP_Bundle_WiiU_CMakeFunction)
    function(TP_Bundle_WiiU_CMakeFunction Target)
        message("TEAPACKET PROFILE: CREATING RPX AUTOMATICALLY")
        wut_create_rpx(${Target})
        if(COMMAND TP_AM_BuildAssets)
            set(TP_WUHB_ASSET_PATH "--content=assets")
        endif()
        add_custom_command(
                TARGET ${Target}
                POST_BUILD
                COMMENT "TEAPACKET PROFILE: MAKING WUHB"
                COMMAND wuhbtool
                "${Target}.rpx"
                "${Target}.wuhb"
                ${TP_WUHB_ASSET_PATH}
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endfunction()
endif ()