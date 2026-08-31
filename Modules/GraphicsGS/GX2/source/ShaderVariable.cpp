/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/VariableType.h"

size_t TP_GfxGS_ShaderVar_GetSize(const TP_GfxGS_VariableType var)
{
    switch (var.baseType)
    {
    case TP_GfxGS_VariableBaseType_Float:
        return sizeof(float) * var.amount;
    case TP_GfxGS_VariableBaseType_Int:
        return sizeof(int) * var.amount;
    case TP_GfxGS_VariableBaseType_UInt:
        return sizeof(unsigned int) * var.amount;
    case TP_GfxGS_VariableBaseType_None:
    default:
        return 0;
    }
}
