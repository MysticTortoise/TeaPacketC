#pragma once

#include "TeaPacket/Graphics/Texture/Format.hpp"
#include "TeaPacket/Graphics/Texture/ImageData.h"

namespace TeaPacket::Graphics
{
    struct ImageData
    {
        void* data;
        tp_u16 pitch;
        tp_u16 width;
        tp_u16 height;
        TextureFormat format;
    };
}