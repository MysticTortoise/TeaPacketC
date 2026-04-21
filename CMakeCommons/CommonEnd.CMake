target_compile_definitions(${PROJECT_NAME} INTERFACE
        TP_DEBUG=${TP_DEBUG})

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