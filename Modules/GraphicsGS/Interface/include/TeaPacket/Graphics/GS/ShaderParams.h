/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Shader.
 */
#ifndef TEAPACKET_GRAPHICS_GS_SHADERPARAMS_H
#define TEAPACKET_GRAPHICS_GS_SHADERPARAMS_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Graphics/GS/VariableType.h"

typedef struct
{
    /**
     * A view of the code to compile the vertex part of this shader.
     * @details Shader code may be in any format - which format to be used is dependent on the Module Implementation.
     * However, GLSL is recommended as a baseline and any Module Implementations that require another language are
     * highly suggested to provide an AssetMixer pass to convert shaders from GLSL to the native language.
     */
    TP_StringView vertexShaderCode;
    /**
     * A view of the code to compile the fragment/pixel part of this shader.
     */
    TP_StringView fragmentShaderCode;
    /**
     * A list of input attributes.
     * @details Each entry in this list maps to an IN attribute in the shader.
     *
     * TP_GfxGS_MeshParams has a more detailed explanation of how these map to the Shader.
     */
    TP_GfxGS_Shader_VarList inputAttributes;
} TP_GfxGS_ShaderParams;

#endif
