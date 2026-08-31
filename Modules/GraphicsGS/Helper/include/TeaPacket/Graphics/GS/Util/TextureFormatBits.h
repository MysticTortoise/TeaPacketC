#ifndef TEAPACKET_GRAPHICS_GS_HELPER_TEXTUREFORMATBITS_H
#define TEAPACKET_GRAPHICS_GS_HELPER_TEXTUREFORMATBITS_H

#include "TeaPacket/Graphics/Common/ImageFormat.h"
#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef TP_ArrayView(tp_u8) TP_GfxGS_Helper_TextureChannelSizes;

/*TP_GfxGS_Helper_TextureChannelSizes TP_GfxGS_Helper_GetTexFormatChannelSize(TP_GfxGS_Texture_Format format);*/
tp_u16 TP_GfxGS_Helper_GetTexFormatBitsPerPixel(TP_Gfx_Image_Format format);
float TP_GfxGS_Helper_GetTexFormatBytesPerPixel(TP_Gfx_Image_Format format);

#ifdef __cplusplus
}
#endif
#endif
