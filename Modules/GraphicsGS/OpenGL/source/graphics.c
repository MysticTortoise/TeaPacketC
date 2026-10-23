#include "TeaPacket/Graphics/GS/Graphics.h"

#include "TeaPacket/Graphics/GS/GL/gl.h"

void TP_GfxGS_ClearColor(TP_Gfx_Color8 clearColor)
{
    glClearColor(
        clearColor.r / 255.0f,
        clearColor.g / 255.0f,
        clearColor.b / 255.0f,
        1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}