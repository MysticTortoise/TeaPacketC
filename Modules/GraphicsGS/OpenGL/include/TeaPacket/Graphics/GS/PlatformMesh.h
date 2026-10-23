#ifndef TEAPACKET_GRAPHICS_GS_GL_PLATFORMMESH_H
#define TEAPACKET_GRAPHICS_GS_GL_PLATFORMMESH_H

#include "TeaPacket/Graphics/GS/GL/gl.h"


struct TP_GfxGS_Mesh
{
    GLuint VBO;
    GLuint VAO;
    GLuint EBO;

    GLsizei drawCount;
};


#endif //TEAPACKET_GRAPHICS_GS_GL_PLATFORMMESH_H