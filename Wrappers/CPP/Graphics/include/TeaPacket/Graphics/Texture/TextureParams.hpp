#pragma once
#include "TeaPacket/Graphics/Texture/TextureParams.h"

#include "TeaPacket/Graphics/Texture/AvailableMode.hpp"
#include "TeaPacket/Graphics/Texture/FilterMode.hpp"
#include "TeaPacket/Graphics/Texture/Format.hpp"
#include "TeaPacket/Graphics/Texture/WrapMode.hpp"

namespace TeaPacket::Graphics
{
    struct TextureUseFlags
    {
        bool shaderResource : 1;
        bool cpuReadable : 1;
        TextureAvailableMode writeMode : 2;
    };

    struct TextureParams
    {
        void* data;
        tp_u16 width;
        tp_u16 height;
        TextureFormat format;
        TextureFilterMode filterMode;
        TextureWrapMode wrapMode;
        TextureUseFlags flags;
    };
}