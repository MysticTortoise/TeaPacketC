/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a ShaderBuffer.
 */
#ifndef TEAPACKET_TEAPACKET_GRAPHICS_SHADERBUFFERPARAMETERS_H
#define TEAPACKET_TEAPACKET_GRAPHICS_SHADERBUFFERPARAMETERS_H
#include <stddef.h>

#include "TeaPacket/Graphics/VariableType.h"


typedef struct
{
    /**
     * The data to populate this ShaderBuffer with initially.
     * @details If nullptr, then this ShaderBuffer will not be initialized.
     */
    void* data;

    /**
     * A description of how this buffer is laid out.
     * @details Each entry in this list must be
     */
    TP_Graphics_Shader_VarList infoList;
} TP_Graphics_ShaderBufferParams;

#endif