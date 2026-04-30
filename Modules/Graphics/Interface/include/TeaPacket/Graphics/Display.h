
#ifndef TEAPACKET_GRAPHICS_DISPLAY_H
#define TEAPACKET_GRAPHICS_DISPLAY_H

#include "TeaPacket/Graphics/DisplayParams.h"
#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Graphics_Display TP_Graphics_Display;
typedef TP_ArrayView(TP_Graphics_DisplayParams) TP_Graphics_DisplayParamList;

typedef tp_u16 TP_Graphics_DisplayID;

void TP_Graphics_InitDefaultDisplays(TP_Graphics_DisplayParamList params);
TP_Graphics_DisplayID TP_Graphics_Display_GetCount(void);

void TP_Graphics_Display_BeginRender(TP_Graphics_DisplayID);
void TP_Graphics_Display_FinishRender(TP_Graphics_DisplayID);

tp_u16 TP_Graphics_Display_GetWidth(TP_Graphics_DisplayID);
tp_u16 TP_Graphics_Display_GetHeight(TP_Graphics_DisplayID);

void TP_Graphics_Display_PresentAll(void);
void TP_Graphics_Display_WaitForVSync(void);



#ifdef __cplusplus
}
#endif
#endif
