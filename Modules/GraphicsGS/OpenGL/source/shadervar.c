/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/GL/gl.h"
#include "TeaPacket/Graphics/GS/VariableType.h"

size_t TP_GfxGS_ShaderVar_GetSize(const TP_GfxGS_VariableType var)
{
    switch (var.baseType)
    {
    case TP_GfxGS_VariableBaseType_Float:
        return sizeof(GLfloat) * var.amount;
    case TP_GfxGS_VariableBaseType_Int:
        return sizeof(GLint) * var.amount;
    case TP_GfxGS_VariableBaseType_UInt:
        return sizeof(GLuint) * var.amount;
    case TP_GfxGS_VariableBaseType_None:
    default:
        return 0;
    }
}
