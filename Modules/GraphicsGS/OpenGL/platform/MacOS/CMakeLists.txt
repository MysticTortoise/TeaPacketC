set(TP_GfxGS_GL_SpecsVer GL CACHE INTERNAL "" FORCE)
set(TP_GfxGS_GL_MajorVer 4 CACHE INTERNAL "" FORCE)
set(TP_GfxGS_GL_MinorVer 1 CACHE INTERNAL "" FORCE)
add_subdirectory(../glad TP_GfxGS_GL_GLAD)

enable_language(OBJC)
TP_add_impl_subdirectory(Window Cocoa)
TP_add_interface_subdirectory(GraphicsGS)

add_library(TP_GfxGS_GL_Platform
        platform.m
)

target_link_libraries(TP_GfxGS_GL_Platform PUBLIC TP_GfxGS_GL_Platform_GLAD
    "-framework Cocoa"
    "-framework OpenGL"
    TeaPacket_Window_Cocoa
    TeaPacket_GraphicsGS_Base
)

target_compile_definitions(TP_GfxGS_GL_Platform PRIVATE GL_SILENCE_DEPRECATION)