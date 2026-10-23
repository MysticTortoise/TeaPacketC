
add_library(TP_GfxGS_GL_Platform_GLAD STATIC source/gl.c)

TP_execute_python_script("${CMAKE_CURRENT_SOURCE_DIR}/glad.py")

set(GLAD_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/glad/")
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)

if("${TP_GfxGS_GL_SpecsVer}" STREQUAL "GL")
    set(TP_GfxGS_GL_SpecsVerP "core")
endif()
message("${TP_GfxGS_GL_SpecsVer}")


glad_add_library(TP_GfxGS_GL_GLAD STATIC REPRODUCIBLE LOADER API
        "gl:${TP_GfxGS_GL_SpecsVerP}=${TP_GfxGS_GL_MajorVer}.${TP_GfxGS_GL_MinorVer}")

TP_add_interface_subdirectory(Types)

target_link_libraries(TP_GfxGS_GL_Platform_GLAD PUBLIC
        TP_GfxGS_GL_GLAD
    TeaPacket_Types_Base)
target_include_directories(TP_GfxGS_GL_Platform_GLAD PUBLIC include)

