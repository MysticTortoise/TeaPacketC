#pragma once
#include "TeaPacket/Graphics/ShaderBufferParams.h"

namespace TeaPacket::Graphics
{
    struct ShaderBufferParams
    {
        void* data;
        size_t size;
    };
}