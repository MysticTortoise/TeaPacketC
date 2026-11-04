file(GLOB_RECURSE sources source/*.cpp)

add_library(LibGLShaderMixer STATIC ${sources})

target_include_directories(LibGLShaderMixer PUBLIC include)
target_include_directories(LibGLShaderMixer PRIVATE source)
target_compile_features(LibGLShaderMixer PRIVATE cxx_std_17)

include(FetchContent)
add_subdirectory(settings_core)
add_subdirectory(glsl_to_spirv)
add_subdirectory(spirv_passer)
add_subdirectory(spirv_to_glsl)

target_link_libraries(LibGLShaderMixer PUBLIC
    LibGLShaderMixer_Settings
)

target_link_libraries(LibGLShaderMixer PRIVATE
        LibGLShaderMixer_GLSLToSpirv
        LibGLShaderMixer_SpirvPasses
        LibGLShaderMixer_SpirvToGLSL)