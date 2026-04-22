if(NOT COMMAND TP_EnumGenerator)
    function(TP_EnumGenerator SourceFile DestFile Target)
        add_custom_command(
                OUTPUT "${DestFile}"
                DEPENDS "${SourceFile}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                COMMENT "Generating ${DestFile} from ${SourceFile}"
                COMMAND python3 "${TEAPACKET_ROOT}/Generators/EnumGenerator/main.py" "${SourceFile}" "${DestFile}"
                VERBATIM
        )
        target_sources(${Target} PUBLIC "${DestFile}")
    endfunction()
endif()