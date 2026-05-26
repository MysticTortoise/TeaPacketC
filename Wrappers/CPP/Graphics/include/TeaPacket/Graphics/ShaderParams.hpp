#pragma once

#include "TeaPacket/Graphics/ShaderParams.h"

#include <string_view>

#include "TeaPacket/Graphics/VariableType.hpp"
#include "TeaPacket/Types/SpanView.hpp"

namespace TeaPacket::Graphics
{
    struct ShaderParams
    {
        std::string_view vertexShaderCode;
        std::string_view fragmentShaderCode;
        SpanView<VariableType> inputAttributes;
    };
}
