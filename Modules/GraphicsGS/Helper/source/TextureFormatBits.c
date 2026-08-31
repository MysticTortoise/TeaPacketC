#include "TeaPacket/Graphics/GS/Util/TextureFormatBits.h"

#include <stdlib.h>

TP_GfxGS_Helper_TextureChannelSizes TP_GfxGS_Helper_GetTexFormatChannelSize(TP_Gfx_Image_Format format)
{
    (void)format;
    /* NOT IMPLEMENTED */
    exit(-1);
}

tp_u16 TP_GfxGS_Helper_GetTexFormatBitsPerPixel(const TP_Gfx_Image_Format format)
{
    switch (format)
    {
    case TP_Gfx_Image_Format_BGRA8:
    case TP_Gfx_Image_Format_RGBA8:
    case TP_Gfx_Image_Format_D24S8: return 32;
    case TP_Gfx_Image_Format_R8: return 8;
    case TP_Gfx_Image_Format_R1: return 1;
    case TP_Gfx_Image_Format_R16: return 16;
    case TP_Gfx_Image_Format_RGB8:
    case TP_Gfx_Image_Format_BGR8: return 8;
    case TP_Gfx_Image_Format_R5G6B5:
    case TP_Gfx_Image_Format_B5G6R5:
    case TP_Gfx_Image_Format_RGB5A1:
    case TP_Gfx_Image_Format_BGR5A1: return 16;
    case TP_Gfx_Image_Format_R2: return 2;
    case TP_Gfx_Image_Format_R4: return 4;
    case TP_Gfx_Image_Format_NONE:
    default: return 0;
    }
}

float TP_GfxGS_Helper_GetTexFormatBytesPerPixel(const TP_Gfx_Image_Format format)
{
    return (float)TP_GfxGS_Helper_GetTexFormatBitsPerPixel(format) / 8.0f;
}
