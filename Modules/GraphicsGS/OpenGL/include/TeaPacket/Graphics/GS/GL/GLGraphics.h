#ifndef TEAPACKET_GRAPHICSGS_OPENGL_GLGRAPHICS_H
#define TEAPACKET_GRAPHICSGS_OPENGL_GLGRAPHICS_H

#include "TeaPacket/Graphics/GS/DisplayParams.h"
#include "TeaPacket/Types/Numeric.h"

tp_bool TP_GfxGS_GL_Init(void);
void TP_GfxGS_GL_DeInit(void);

void TP_GfxGS_GL_CreateWindow(TP_GfxGS_DisplayParams params);

#endif //TEAPACKET_GRAPHICSGS_OPENGL_GLGRAPHICS_H
