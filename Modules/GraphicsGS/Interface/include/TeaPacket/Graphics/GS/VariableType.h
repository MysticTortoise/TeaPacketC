/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* TP_GfxGS_VariableType is a struct that describes a type in a Shader.
 */
#ifndef TEAPACKET_GRAPHICS_GS_VARIABLETYPE_H
#define TEAPACKET_GRAPHICS_GS_VARIABLETYPE_H

#include "TeaPacket/Graphics/GS/VariableBaseType.h"
#include "TeaPacket/Types/Array.h"

typedef struct
{
    /**
     * The integral type of this type.
     */
    TP_GfxGS_VariableBaseType baseType;
    /**
     * The vector size of this type.
     * @details 1 maps to a singular of this type (i.e. baseType = float, amount = 1 is a float).
     * Any number above that maps to a vector of this type (i.e. baseType=float, amount = 4 is a float4 or vec4)
     *
     * Any amount above the highest supported by this module implementation (typically 4) is undefined behavior.
     */
    tp_u8 amount;
} TP_GfxGS_VariableType;

#define TP_GfxGS_VariableType_SINT {TP_GfxGS_VariableBaseType_Int, 1}
#define TP_GfxGS_VariableType_UINT {TP_GfxGS_VariableBaseType_UInt, 1}
#define TP_GfxGS_VariableType_FLOAT {TP_GfxGS_VariableBaseType_Float, 1}

#define TP_GfxGS_VariableType_IVEC2 {TP_GfxGS_VariableBaseType_Int, 2}
#define TP_GfxGS_VariableType_UVEC2 {TP_GfxGS_VariableBaseType_UInt, 2}
#define TP_GfxGS_VariableType_FVEC2 {TP_GfxGS_VariableBaseType_Float, 2}

#define TP_GfxGS_VariableType_IVEC3 {TP_GfxGS_VariableBaseType_Int, 3}
#define TP_GfxGS_VariableType_UVEC3 {TP_GfxGS_VariableBaseType_UInt, 3}
#define TP_GfxGS_VariableType_FVEC3 {TP_GfxGS_VariableBaseType_Float, 3}

#define TP_GfxGS_VariableType_IVEC4 {TP_GfxGS_VariableBaseType_Int, 4}
#define TP_GfxGS_VariableType_UVEC4 {TP_GfxGS_VariableBaseType_UInt, 4}
#define TP_GfxGS_VariableType_FVEC4 {TP_GfxGS_VariableBaseType_Float, 4}

typedef TP_ArrayView(TP_GfxGS_VariableType) TP_GfxGS_Shader_VarList;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Gets the size of a Type on the GPU. Some types are padded, and this will account for that.
 * @return The size of the given type, in bytes.
 */
size_t TP_GfxGS_ShaderVar_GetSize(TP_GfxGS_VariableType);

#ifdef __cplusplus
}


#endif


#endif
