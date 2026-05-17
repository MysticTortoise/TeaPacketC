#pragma once

#include "../../../../../../Modules/Graphics/Interface/include/TeaPacket/Graphics/ShaderParams.h"

#include <string_view>
#include <span>

#include "TeaPacket/Graphics/VariableType.hpp"

namespace TeaPacket::Graphics
{
    struct ShaderParams
    {
        std::string_view vertexShaderCode;
        std::string_view fragmentShaderCode;
        std::span<VariableType> inputAttributes;
    };
}