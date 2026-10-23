if(NOT DEFINED TeaPacket_GraphicsGS_OpenGL_Platform)
    if(DEFINED TEAPACKET_PLATFORM)
        set(TeaPacket_GraphicsGS_OpenGL_Platform ${TEAPACKET_PLATFORM})
    endif ()
endif ()

if(NOT DEFINED TeaPacket_GraphicsGS_OpenGL_Platform)
    message(FATAL_ERROR "No OpenGL platform specified!")
endif()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/${TeaPacket_GraphicsGS_OpenGL_Platform}")