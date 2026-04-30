#ifndef TEAPACKET_GRAPHICS_HELPER_TEXTUREFORMATBITS_H
#define TEAPACKET_GRAPHICS_HELPER_TEXTUREFORMATBITS_H

#include "TeaPacket/Graphics/Texture/Format.h"
#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef TP_ArrayView(tp_u8) TP_Graphics_Helper_TextureChannelSizes;

/*TP_Graphics_Helper_TextureChannelSizes TP_Graphics_Helper_GetTexFormatChannelSize(TP_Graphics_Texture_Format format);*/
tp_u16 TP_Graphics_Helper_GetTexFormatBitsPerPixel(TP_Graphics_Texture_Format format);
float TP_Graphics_Helper_GetTexFormatBytesPerPixel(TP_Graphics_Texture_Format format);

#ifdef __cplusplus
}
#endif
#endif
