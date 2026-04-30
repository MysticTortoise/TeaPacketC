
#ifndef TEAPACKET_GRAPHICS_H
#define TEAPACKET_GRAPHICS_H

#include "TeaPacket/Types/Numeric.h"


#ifdef __cplusplus
extern "C" {
#endif


tp_bool TP_Graphics_Init(void);
void TP_Graphics_DeInit(void);

void TP_Graphics_DrawMesh(void);
void TP_Graphics_ClearColor(tp_u8 r, tp_u8 g, tp_u8 b);

void TP_Graphics_SetDepthEnabled(tp_bool depthEnabled);

#ifdef __cplusplus
}
#endif
#endif
