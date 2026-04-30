#ifndef TEAPACKET_GRAPHICS_SHADER_VARIABLETYPE_H
#define TEAPACKET_GRAPHICS_SHADER_VARIABLETYPE_H

#include "TeaPacket/Graphics/Shader/VariableBaseType.h"
#include "TeaPacket/Types/Array.h"

typedef struct
{
    TP_Graphics_Shader_VariableBaseType baseType;
    tp_u8 amount;
} TP_Graphics_Shader_VariableType;

typedef TP_ArrayView(TP_Graphics_Shader_VariableType) TP_Graphics_Shader_VarList;

#ifdef __cplusplus
extern "C" {
#endif

size_t TP_Graphics_ShaderVar_GetSize(TP_Graphics_Shader_VariableType);

#ifdef __cplusplus
}


#endif


#endif
