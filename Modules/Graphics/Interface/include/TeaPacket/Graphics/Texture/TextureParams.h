/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Texture.
 */

#ifndef TEAPACKET_GRAPHICS_TEXTUREPARAMS_H
#define TEAPACKET_GRAPHICS_TEXTUREPARAMS_H

#include "TeaPacket/Graphics/Texture/AvailableMode.h"
#include "TeaPacket/Graphics/Texture/FilterMode.h"
#include "TeaPacket/Graphics/Texture/Format.h"
#include "TeaPacket/Graphics/Texture/WrapMode.h"
#include "TeaPacket/Types/Numeric.h"

/**
 * Contains flags determining how a Texture should be used.
 */
typedef struct
{
    /**
     * Whether this Texture is to be used by a shader. Almost always TRUE.
     */
    tp_bool shaderResource : 1;
    /**
     * Whether this Texture should be readable by the CPU. Reccomended default is FALSE.
     */
    tp_bool cpuReadable : 1;
    /**
     * The write accessibility of the Texture.
     */
    TP_Graphics_Texture_AvailableMode writeMode : 2;
} TP_Graphics_TextureUseFlags;

/**
 * Contains parameters for determining how a Texture should be created.
 */
typedef struct
{
    /**
     * A pointer to the data to be used to fill the texture. The format of that data depends on the foramt of this Texture.
     */
    void* data;
    /**
     * The pitch of the texture. This defines how many bytes one row of pixels is.
     * @details If 0, then the width of the image multiplied by the bytes per pixel of the format should be used as the pitch.
     */
    tp_u16 pitch;
    /**
     * The width of the Texture, in pixels.
     */
    tp_u16 width;
    /**
     * The height of the Texture, in pixels.
     */
    tp_u16 height;
    /**
     * The format of the Texture.
     */
    TP_Graphics_Texture_Format format;
    /**
     * How the texture is filtered when sampled from.
     */
    TP_Graphics_Texture_FilterMode filterMode;
    /**
     * How the texture is sampled from when UVs are out of the 0-1 range.
     */
    TP_Graphics_Texture_WrapMode wrapMode;
    /**
     * Flags determining how the texture should be used.
     */
    TP_Graphics_TextureUseFlags flags;
} TP_Graphics_TextureParams;


#endif
