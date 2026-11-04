FetchContent_Declare(
        spirv-tools
        GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Tools.git
        GIT_TAG v2026.3
        GIT_SHALLOW TRUE
        GIT_SUBMODULES_RECURSE TRUE
)
set(SPIRV_SKIP_EXECUTABLES ON CACHE BOOL "" FORCE)
set(SPIRV_SKIP_TESTS ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        spirv-headers
        GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Headers.git
        GIT_TAG        v1.202609.0
        GIT_SHALLOW TRUE
        GIT_SUBMODULES_RECURSE TRUE
)
set(SPIRV_HEADERS_SKIP_EXAMPLES ON  CACHE INTERNAL "")
set(SPIRV_HEADERS_SKIP_INSTALL  ON  CACHE INTERNAL "")
set(SPIRV_SKIP_TESTS            ON  CACHE INTERNAL "Disable SPIRV-Tools tests")
set(SPIRV_SKIP_EXECUTABLES      ON CACHE INTERNAL "")


FetchContent_MakeAvailable(spirv-headers spirv-tools)

add_library(SPIRV-Tools-opt-PassLib INTERFACE)
target_link_libraries(SPIRV-Tools-opt-PassLib INTERFACE SPIRV-Tools-opt)

target_include_directories(SPIRV-Tools-opt-PassLib INTERFACE
        "${spirv-tools_SOURCE_DIR}"
        "${spirv-tools_SOURCE_DIR}/include"
        "${spirv-tools_BINARY_DIR}"
)

target_link_libraries(LibGLShaderMixer_SpirvPasses PRIVATE
        SPIRV-Tools-opt-PassLib)

target_compile_features(SPIRV-Tools-opt PUBLIC cxx_std_17)