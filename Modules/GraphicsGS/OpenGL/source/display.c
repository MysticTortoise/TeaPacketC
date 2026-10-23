#include "TeaPacket/Graphics/GS/Display.h"

#include "TeaPacket/Graphics/GS/GL/GLGraphics.h"
#include "TeaPacket/Logging/Logging.h"


void TP_GfxGS_InitDefaultDisplays(TP_GfxGS_DisplayParamList params)
{
    for (size_t i = 0; i < params.size; i++)
    {
        TP_GfxGS_GL_CreateWindow(params.p[i]);
    }
}
