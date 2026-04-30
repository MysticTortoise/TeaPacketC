#pragma once
#include <gx2/enum.h>
#include "TeaPacket/Graphics/Shader/VariableType.h"
#include <stdexcept>
#include <gx2/utils.h>

namespace TeaPacket::Graphics::GX2
{
    constexpr GX2AttribFormat GetGX2AttribFormatFromShaderVarType(const TP_Graphics_Shader_VariableType variableType)
    {
        switch (variableType.baseType)
        {
        case TP_Graphics_Shader_VariableBaseType_Float:
            switch (variableType.amount)
            {
        case 1: return GX2_ATTRIB_FORMAT_FLOAT_32;
        case 2: return GX2_ATTRIB_FORMAT_FLOAT_32_32;
        case 3: return GX2_ATTRIB_FORMAT_FLOAT_32_32_32;
        case 4: return GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32;
                default: throw std::runtime_error("Bad Value");;
            }
        case TP_Graphics_Shader_VariableBaseType_Int:
            switch (variableType.amount)
            {
        case 1: return GX2_ATTRIB_FORMAT_SINT_8;
        case 2: return GX2_ATTRIB_FORMAT_SINT_8_8;
        case 3: throw std::runtime_error("Vec3 of SInts not supported :(");
        case 4: return GX2_ATTRIB_FORMAT_SINT_8_8_8_8;
                default: throw std::runtime_error("Bad Value");;
            }
        case TP_Graphics_Shader_VariableBaseType_UInt:
            switch (variableType.amount)
            {
        case 1: return GX2_ATTRIB_FORMAT_UINT_8;
        case 2: return GX2_ATTRIB_FORMAT_UINT_8_8;
        case 3: throw std::runtime_error("Vec3 of UInts not supported :(");
        case 4: return GX2_ATTRIB_FORMAT_UINT_8_8_8_8;
                default: throw std::runtime_error("Bad Value");;
            }
        case TP_Graphics_Shader_VariableBaseType_None:
            break;
        }
        throw std::runtime_error("Bad Value");
    }

    constexpr uint32_t GfxGetAttribFormatSel(const GX2AttribFormat format)
        {
            switch (format) {
            case GX2_ATTRIB_FORMAT_UNORM_8:
            case GX2_ATTRIB_FORMAT_UINT_8:
            case GX2_ATTRIB_FORMAT_SNORM_8:
            case GX2_ATTRIB_FORMAT_SINT_8:
            case GX2_ATTRIB_FORMAT_FLOAT_32:
                return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
            case GX2_ATTRIB_FORMAT_UNORM_8_8:
            case GX2_ATTRIB_FORMAT_UINT_8_8:
            case GX2_ATTRIB_FORMAT_SNORM_8_8:
            case GX2_ATTRIB_FORMAT_SINT_8_8:
            case GX2_ATTRIB_FORMAT_FLOAT_32_32:
                return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
            case GX2_ATTRIB_FORMAT_FLOAT_32_32_32:
                return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_Z, GX2_SQ_SEL_1);
            case GX2_ATTRIB_FORMAT_UNORM_8_8_8_8:
            case GX2_ATTRIB_FORMAT_UINT_8_8_8_8:
            case GX2_ATTRIB_FORMAT_SNORM_8_8_8_8:
            case GX2_ATTRIB_FORMAT_SINT_8_8_8_8:
            case GX2_ATTRIB_FORMAT_FLOAT_32_32_32_32:
                return GX2_SEL_MASK(GX2_SQ_SEL_X, GX2_SQ_SEL_Y, GX2_SQ_SEL_Z, GX2_SQ_SEL_W);
                break;
            default:
                return GX2_SEL_MASK(GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_0, GX2_SQ_SEL_1);
            }
        }
}
