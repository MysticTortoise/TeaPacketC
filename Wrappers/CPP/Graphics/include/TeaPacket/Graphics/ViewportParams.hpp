#pragma once
#include "TeaPacket/Graphics/ViewportParams.h"

namespace TeaPacket::Graphics
{
    struct ViewportParams
    {
        tp_u16 width, height;
        bool shaderUsable;
    };
}