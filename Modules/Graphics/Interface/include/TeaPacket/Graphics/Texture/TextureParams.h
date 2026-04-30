#ifndef TEAPACKET_GRAPHICS_TEXTUREPARAMS_H
#define TEAPACKET_GRAPHICS_TEXTUREPARAMS_H

#include "TeaPacket/Types/Numeric.h"

#include "TeaPacket/Graphics/Texture/Format.h"
#include "TeaPacket/Graphics/Texture/FilterMode.h"
#include "TeaPacket/Graphics/Texture/WrapMode.h"
#include "TeaPacket/Graphics/Texture/AvailableMode.h"

typedef struct
{
    tp_bool shaderResource : 1;
    tp_bool cpuReadable : 1;
    TP_Graphics_Texture_AvailableMode writeMode : 2;

} TP_Graphics_TextureUseFlags;

typedef struct
{
    void* data;
    tp_u16 width;
    tp_u16 height;
    TP_Graphics_Texture_Format format;
    TP_Graphics_Texture_FilterMode filterMode;
    TP_Graphics_Texture_WrapMode wrapMode;
    TP_Graphics_TextureUseFlags flags;

} TP_Graphics_TextureParams;



#endif
