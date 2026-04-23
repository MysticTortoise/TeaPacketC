
#ifndef TEAPACKET_WINDOW_H
#define TEAPACKET_WINDOW_H

#include "TeaPacket/Window/WindowParams.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Window TP_Window;

TP_Window* TP_Window_Create(const TP_Window_Params* params);
void TP_Window_Destroy(TP_Window*);

void TP_Window_ProcessEvents(TP_Window*);

size_t TP_Window_GetCount(void);
TP_Window* TP_Window_Get(size_t index);

tp_u16 TP_Window_GetXPos(TP_Window*);
tp_u16 TP_Window_GetYPos(TP_Window*);
tp_u16 TP_Window_GetWidth(TP_Window*);
tp_u16 TP_Window_GetHeight(TP_Window*);

TP_String TP_Window_GetTitle(TP_Window*);

void TP_Window_SetXPos(TP_Window*, tp_u16 xPos);
void TP_Window_SetYPos(TP_Window*, tp_u16 yPos);
void TP_Window_SetWidth(TP_Window*, tp_u16 width);
void TP_Window_SetHeight(TP_Window*, tp_u16 height);

void TP_Window_SetTitle(TP_Window*, TP_StringView name);



#ifdef __cplusplus
}
#endif
#endif
