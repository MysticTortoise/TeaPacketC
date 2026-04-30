#include "TeaPacket/Graphics/Util/TextureFormatBits.h"

#include <stdlib.h>

TP_Graphics_Helper_TextureChannelSizes TP_Graphics_Helper_GetTexFormatChannelSize(TP_Graphics_Texture_Format format)
{
    (void)format;
    /* NOT IMPLEMENTED */
    exit(-1);
}

tp_u16 TP_Graphics_Helper_GetTexFormatBitsPerPixel(const TP_Graphics_Texture_Format format)
{
    switch (format)
    {
    case TP_Graphics_Texture_Format_BGRA8:
    case TP_Graphics_Texture_Format_RGBA8:
    case TP_Graphics_Texture_Format_D24S8: return 32;
    case TP_Graphics_Texture_Format_R8: return 8;
    case TP_Graphics_Texture_Format_R1: return 1;
    case TP_Graphics_Texture_Format_NONE:
    default: return 0;
    }
}

float TP_Graphics_Helper_GetTexFormatBytesPerPixel(const TP_Graphics_Texture_Format format)
{
    return (float)TP_Graphics_Helper_GetTexFormatBitsPerPixel(format) / 8.0f;
}
