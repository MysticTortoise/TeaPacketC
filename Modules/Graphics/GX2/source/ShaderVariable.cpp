#include "TeaPacket/Graphics/Shader/VariableType.h"

#include <stdexcept>

size_t TP_Graphics_ShaderVar_GetSize(const TP_Graphics_Shader_VariableType var)
{
    switch (var.baseType)
    {
    case TP_Graphics_Shader_VariableBaseType_Float:
        return sizeof(float) * var.amount;
    case TP_Graphics_Shader_VariableBaseType_Int:
        return sizeof(int) * var.amount;
    case TP_Graphics_Shader_VariableBaseType_UInt:
        return sizeof(unsigned int) * var.amount;
    case TP_Graphics_Shader_VariableBaseType_None:
    default:
        return 0;
    }
}