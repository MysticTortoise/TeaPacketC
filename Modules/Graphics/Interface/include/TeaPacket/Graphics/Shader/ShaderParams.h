#ifndef TEAPACKET_GRAPHICS_SHADERPARAMS_H
#define TEAPACKET_GRAPHICS_SHADERPARAMS_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Graphics/Shader/VariableType.h"

typedef struct
{
    TP_StringView vertexShaderCode;
    TP_StringView fragmentShaderCode;
    TP_Graphics_Shader_VarList inputAttributes;
} TP_Graphics_ShaderParams;

#endif
