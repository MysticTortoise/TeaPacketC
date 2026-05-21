if(NOT COMMAND TP_EnumGenerator)
    function(TP_EnumGenerator SourceFile DestFile Target)
        add_custom_command(
                OUTPUT "${DestFile}"
                DEPENDS "${SourceFile}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                COMMENT "Generating ${DestFile} from ${SourceFile}"
                COMMAND python "${TEAPACKET_ROOT}/Generators/EnumGenerator/main.py" cgen "${SourceFile}" "${DestFile}"
                VERBATIM
        )
        target_sources(${Target} PUBLIC "${DestFile}")
    endfunction()
endif()

if(NOT COMMAND TP_EnumGenerator_CPPWrap)
    function(TP_EnumGenerator_CPPWrap SourceFile DestFile OGPath Target)
        if(${ARGC} GREATER_EQUAL 5)
            set(NamespaceRemoval ${ARGV4})
        endif ()

        add_custom_command(
                OUTPUT "${DestFile}"
                DEPENDS "${SourceFile}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                COMMENT "Generating ${DestFile} from ${SourceFile}"
                COMMAND python "${TEAPACKET_ROOT}/Generators/EnumGenerator/main.py" cppgen
                "${SourceFile}" "${DestFile}" "${OGPath}" ${NamespaceRemoval}
                VERBATIM
        )
        target_sources(${Target} PUBLIC "${DestFile}")
    endfunction()
endif()