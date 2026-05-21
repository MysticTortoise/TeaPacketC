/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Shader.
 */
#ifndef TEAPACKET_GRAPHICS_SHADERPARAMS_H
#define TEAPACKET_GRAPHICS_SHADERPARAMS_H

#include "TeaPacket/Types/Array.h"
#include "VariableType.h"

typedef struct
{
    /**
     * A view of the code to compile the vertex part of this shader.
     * @details Shader code may be in any format - which format to be used is dependent on the Module Implementation.
     * However, GLSL is reccomended as a baseline and any Module Implementations that require another language are
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
     * TP_Graphics_MeshParams has a more detailed explanation of how these map to the Shader.
     */
    TP_Graphics_Shader_VarList inputAttributes;
} TP_Graphics_ShaderParams;

#endif
