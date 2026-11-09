include("${TEAPACKET_ROOT}/CMakeCommons/CommonFunctions.CMake")


if(NOT COMMAND TP_EnumMapGen)
    function(TP_EnumMapGen Source Target)
        set(options C_MODE)
        set(oneValueArgs MAX_FROM)

        cmake_parse_arguments(PARSE_ARGV 0 TP_EnumMapGen
            "${options}" "${oneValueArgs}" ""
        )



        if(${TP_EnumMapGen_C_MODE})
            set(c_arg "--c_mode")
        endif ()

        if(${TP_EnumMapGen_MAX_FROM})
            set(max_from --max_from ${TP_EnumMapGen_MAX_FROM})
        endif ()


        file(READ "${Source}" FILE_CONTENTS)
        string(REPLACE "\n" ";" FILE_LINES "${FILE_CONTENTS}")
        list(GET FILE_LINES 0 FIRST_LINE)#
        string(REPLACE "Destination " "" DEST_FILE "${FIRST_LINE}")
        
        TP_get_python()
        
        add_custom_command(
                OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/include/${DEST_FILE}"
                DEPENDS "${Source}"
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                COMMENT "Generating ${DEST_FILE} from ${Source}"
                COMMAND ${TP_PYTHON_NAME} "${TEAPACKET_ROOT}/Generators/EnumMapGen/main.py" "${Source}" "${c_arg}" ${max_from}
                VERBATIM
        )
        target_sources(${Target} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/${DEST_FILE}")
    endfunction()
endif()