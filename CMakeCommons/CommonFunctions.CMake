if(NOT COMMAND add_subdirectory_no_overwrite)
    function(add_subdirectory_no_overwrite target_name subdirectory internalDir)
        if(NOT TARGET ${target_name})
            add_subdirectory(${subdirectory} ${internalDir})
        endif()
    endfunction()
endif()

if(NOT COMMAND TP_add_interface_subdirectory)
    function(TP_add_interface_subdirectory interfaceName)
        set(target_name TeaPacket_${interfaceName}_Base)
        set(subdir "${TEAPACKET_ROOT}/Modules/${interfaceName}/Interface")
        if(NOT TARGET ${target_name})
            add_subdirectory_no_overwrite(${target_name} ${subdir} "${interfaceName}Base")
        endif()
    endfunction()
endif()

if(NOT COMMAND TP_add_impl_subdirectory)
    function(TP_add_impl_subdirectory moduleName implName)
        message(${moduleName}${implName})
        set(target_name TeaPacket_${moduleName}_${implName})
        set(subdir "${TEAPACKET_ROOT}/Modules/${moduleName}/${implName}")
        if(NOT TARGET ${target_name})
            add_subdirectory_no_overwrite(${target_name} ${subdir} "${moduleName}${implName}")
            target_compile_definitions(${target_name} PUBLIC "TeaPacket_${moduleName}_Implemented")
        endif()
    endfunction()
endif()

if(NOT COMMAND TP_add_extension_subdirectory)
    function(TP_add_extension_subdirectory extensionName)
        message(${extensionName})
        set(target_name TeaPacket_Extension_${extensionName})
        set(subdir "${TEAPACKET_ROOT}/Extensions/${extensionName}")
        if(NOT TARGET ${target_name})
            add_subdirectory_no_overwrite(${target_name} ${subdir} "${extensionName}")
        endif()
    endfunction()
endif()

if(NOT COMMAND TP_add_bundle)
    function(TP_add_bundle bundleName targetName)
        set(TEAPACKET_BUNDLE_TARGET ${targetName})
        include("${TEAPACKET_ROOT}/Bundles/${bundleName}.CMake")
    endfunction()
endif()

if(NOT COMMAND TP_run_python_script)
    function(TP_run_python_script projectName scriptPath)
        cmake_path(GET scriptPath PARENT_PATH scriptDir)
        add_custom_command(
                TARGET ${projectName}
                PRE_BUILD
                COMMENT "Running ${scriptPath}"
                COMMAND python3 ${scriptPath}
                WORKING_DIRECTORY "${scriptDir}"
                VERBATIM
        )
    endfunction()
endif()