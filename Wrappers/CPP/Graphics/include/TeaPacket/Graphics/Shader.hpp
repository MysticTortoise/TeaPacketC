#pragma once

#include "../../../../../../Modules/Graphics/Interface/include/TeaPacket/Graphics/Shader.h"

#include "TeaPacket/Graphics/ShaderParams.hpp"
#include "TeaPacket/Types/ClassDef.hpp"
#include "TeaPacket/Types/StringView.hpp"
#include "TeaPacket/Types/TPArray.hpp"

namespace TeaPacket::Graphics
{
    class Shader
    {
        TP_ClassWrapperDef(Shader, TP_Graphics)

        explicit Shader(const ShaderParams& params):
        Shader(TP_Graphics_ShaderParams{
            .vertexShaderCode = Types::StringViewToTP(params.vertexShaderCode),
            .fragmentShaderCode = Types::StringViewToTP(params.fragmentShaderCode),
            .inputAttributes = SpanToTPArrayCast(params.inputAttributes, TP_Graphics_VariableType),
        })
        {}

        void SetActive() const
        {
            TP_Graphics_Shader_SetActive(p);
        }
    };
}
