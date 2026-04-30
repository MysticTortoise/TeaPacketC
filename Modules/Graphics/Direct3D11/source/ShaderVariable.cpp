#include "TeaPacket/Graphics/Shader/VariableType.h"

#include <stdexcept>

#include "DirectXMath.h"

size_t TP_Graphics_ShaderVar_GetSize(const TP_Graphics_Shader_VariableType type)
{
    switch (type.baseType)
    {
    case TP_Graphics_Shader_VariableBaseType_Float:
        switch (type.amount)
        {
    case 1: return sizeof(float);
    case 2: return sizeof(DirectX::XMFLOAT2);
    case 3: return sizeof(DirectX::XMFLOAT3);
    case 4: return sizeof(DirectX::XMFLOAT4);
    default: break;
        }
        break;
    case TP_Graphics_Shader_VariableBaseType_Int:
        switch (type.amount)
        {
    case 1: return sizeof(int32_t);
    case 2: return sizeof(DirectX::XMINT2);
    case 3: return sizeof(DirectX::XMINT3);
    case 4: return sizeof(DirectX::XMINT4);
    default: break;
        }
        break;
    case TP_Graphics_Shader_VariableBaseType_UInt:
        switch (type.amount)
        {
    case 1: return sizeof(uint32_t);
    case 2: return sizeof(DirectX::XMUINT2);
    case 3: return sizeof(DirectX::XMUINT3);
    case 4: return sizeof(DirectX::XMUINT4);
    default: break;
        }
        break;
    case TP_Graphics_Shader_VariableBaseType_None:
        return 0;
    }
    return 0;
}