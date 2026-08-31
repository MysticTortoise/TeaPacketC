/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/VariableType.h"

#include "DirectXMath.h"

size_t TP_GfxGS_ShaderVar_GetSize(const TP_GfxGS_VariableType type)
{
    switch (type.baseType)
    {
    case TP_GfxGS_VariableBaseType_Float:
        switch (type.amount)
        {
    case 1: return sizeof(float);
    case 2: return sizeof(DirectX::XMFLOAT2);
    case 3: return sizeof(DirectX::XMFLOAT3);
    case 4: return sizeof(DirectX::XMFLOAT4);
    default: break;
        }
        break;
    case TP_GfxGS_VariableBaseType_Int:
        switch (type.amount)
        {
    case 1: return sizeof(int32_t);
    case 2: return sizeof(DirectX::XMINT2);
    case 3: return sizeof(DirectX::XMINT3);
    case 4: return sizeof(DirectX::XMINT4);
    default: break;
        }
        break;
    case TP_GfxGS_VariableBaseType_UInt:
        switch (type.amount)
        {
    case 1: return sizeof(uint32_t);
    case 2: return sizeof(DirectX::XMUINT2);
    case 3: return sizeof(DirectX::XMUINT3);
    case 4: return sizeof(DirectX::XMUINT4);
    default: break;
        }
        break;
    case TP_GfxGS_VariableBaseType_None:
    default:
        return 0;
    }
    return 0;
}