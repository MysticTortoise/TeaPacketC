if(DEFINED TP_DEBUG)
    #message(${TP_DEBUG})

    get_target_property(TP_TARG_TYPE ${PROJECT_NAME} TYPE)

    if(${TP_TARG_TYPE} STREQUAL "INTERFACE_LIBRARY")
        set(TP_TARG_TYPE INTERFACE)
    else ()
        set(TP_TARG_TYPE PUBLIC)
    endif ()
    target_compile_definitions(${PROJECT_NAME} ${TP_TARG_TYPE}
            TP_DEBUG=${TP_DEBUG})
endif ()

# Enable warnings and treat warnings as errors.
if(MSVC)
    target_compile_options(${PROJECT_NAME} INTERFACE /W4 /WX /we4062)
else()
    target_compile_options(${PROJECT_NAME} INTERFACE
            -Wall -Wextra -Wpedantic -Werror
    )
endif()
# Disable extensions and require
set_target_properties(${PROJECT_NAME} PROPERTIES
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
)