if(NOT COMMAND TP_InT_VerifyModuleCoverage)
    function(TP_InT_VerifyModuleCoverage targetName include_dir)
        get_target_property(LIB_FOLDER ${targetName} ARCHIVE_OUTPUT_DIRECTORY)

        if(NOT LIB_FOLDER)
            if(CMAKE_LIBRARY_OUTPUT_DIRECTORY)
                set(LIB_FOLDER "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
            else()
                set(LIB_FOLDER "${CMAKE_CURRENT_BINARY_DIR}")
            endif()
        endif()

        TP_get_python()
        add_custom_command(
                TARGET ${targetName}
                POST_BUILD
                COMMENT "Checking module coverage for ${include_dir}"
                COMMAND ${TP_PYTHON_NAME}
                    "${TEAPACKET_ROOT}/Subtools/InspecTea/check_module_coverage.py"
                    ${include_dir}
                    "${LIB_FOLDER}"
        )
    endfunction()
endif()