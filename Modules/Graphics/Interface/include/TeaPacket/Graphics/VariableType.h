/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* TP_Graphics_VariableType is a struct that describes a type in a Shader.
 */
#ifndef TEAPACKET_GRAPHICS_SHADER_VARIABLETYPE_H
#define TEAPACKET_GRAPHICS_SHADER_VARIABLETYPE_H

#include "VariableBaseType.h"
#include "TeaPacket/Types/Array.h"

typedef struct
{
    /**
     * The integral type of this type.
     */
    TP_Graphics_VariableBaseType baseType;
    /**
     * The vector size of this type.
     * @details 1 maps to a singular of this type (i.e. baseType = float, amount = 1 is a float).
     * Any number above that maps to a vector of this type (i.e. baseType=float, amount = 4 is a float4 or vec4)
     *
     * Any amount above the highest supported by this module implementation (typically 4) is undefined behavior.
     */
    tp_u8 amount;
} TP_Graphics_VariableType;

typedef TP_ArrayView(TP_Graphics_VariableType) TP_Graphics_Shader_VarList;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets the size of a Type on the GPU. Some types are padded, and this will account for that.
 * @return The size of the given type, in bytes.
 */
size_t TP_Graphics_ShaderVar_GetSize(TP_Graphics_VariableType);

#ifdef __cplusplus
}


#endif


#endif
