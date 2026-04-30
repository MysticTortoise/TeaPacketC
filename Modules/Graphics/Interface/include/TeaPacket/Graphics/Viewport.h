
#ifndef TEAPACKET_GRAPHICS_VIEWPORT_H
#define TEAPACKET_GRAPHICS_VIEWPORT_H

#include "TeaPacket/Graphics/ViewportParams.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Graphics_Viewport TP_Graphics_Viewport;

TP_Graphics_Viewport* TP_Graphics_Viewport_Create(TP_Graphics_ViewportParams* params);
void TP_Graphics_Viewport_Destroy(const TP_Graphics_Viewport*);

void TP_Graphics_Viewport_BeginRender(TP_Graphics_Viewport*);
void TP_Graphics_Viewport_FinishRender(TP_Graphics_Viewport*);

tp_u16 TP_Graphics_Viewport_GetWidth(TP_Graphics_Viewport*);
tp_u16 TP_Graphics_Viewport_GetHeight(TP_Graphics_Viewport*);

#ifdef __cplusplus
}
#endif
#endif
