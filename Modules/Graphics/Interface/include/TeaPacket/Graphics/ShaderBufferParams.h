/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a ShaderBuffer.
 */
#ifndef TEAPACKET_TEAPACKET_GRAPHICS_SHADERBUFFERPARAMETERS_H
#define TEAPACKET_TEAPACKET_GRAPHICS_SHADERBUFFERPARAMETERS_H
#include <stddef.h>


typedef struct
{
    /**
     * The data to populate this ShaderBuffer with initially.
     * @details If nullptr, then this ShaderBuffer will not be initialized.
     */
    void* data;
    /**
     * The size of this ShaderBuffer, in bytes.
     */
    size_t size;
} TP_Graphics_ShaderBufferParams;

#endif