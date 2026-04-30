#ifndef TEAPACKET_GRAPHICS_TEXTURE_H
#define TEAPACKET_GRAPHICS_TEXTURE_H

#include "TeaPacket/Graphics/Texture/TextureParams.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Graphics_Texture TP_Graphics_Texture;


TP_Graphics_Texture* TP_Graphics_Texture_Create(TP_Graphics_TextureParams*);
void TP_Graphics_Texture_Destroy(TP_Graphics_Texture*);

tp_u16 TP_Graphics_Texture_GetWidth(TP_Graphics_Texture*);
tp_u16 TP_Graphics_Texture_GetHeight(TP_Graphics_Texture*);
TP_Graphics_Texture_Format TP_Graphics_Texture_GetFormat(TP_Graphics_Texture*);

void TP_Graphics_Texture_SetActive(TP_Graphics_Texture* texture, tp_u8 slot);

tp_bool TP_Graphics_Texture_IsFormatSupported(TP_Graphics_Texture_Format format);

#ifdef __cplusplus
}
#endif
#endif
