#ifndef TEAPACKET_GRAPHICS_GS_GL_PLATFORMVIEWPORT_H
#define TEAPACKET_GRAPHICS_GS_GL_PLATFORMVIEWPORT_H

#include "TeaPacket/Graphics/GS/GL/gl.h"
#include "TeaPacket/Types/Numeric.h"


struct TP_GfxGS_Viewport
{
    GLuint fbo;
    GLuint colorTex;
    GLuint depthTex;

    unsigned int width, height;
};


#endif //TEAPACKET_GRAPHICS_GS_GL_PLATFORMVIEWPORT_H