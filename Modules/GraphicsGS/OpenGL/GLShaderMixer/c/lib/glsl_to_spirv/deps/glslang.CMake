FetchContent_Declare(
        glslang
        GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
        GIT_TAG 16.6.0
)
set(ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "" FORCE)
set(ENABLE_SPVREMAP OFF CACHE BOOL "" FORCE)
set(ENABLE_HLSL OFF CACHE BOOL "" FORCE)
set(ENABLE_OPT OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glslang)

target_link_libraries(LibGLShaderMixer_GLSLToSpirv PRIVATE
        glslang::glslang
        glslang::glslang-default-resource-limits)