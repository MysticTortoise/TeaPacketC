/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Texture.
 */

#ifndef TEAPACKET_GRAPHICS_GS_TEXTUREPARAMS_H
#define TEAPACKET_GRAPHICS_GS_TEXTUREPARAMS_H

#include "TeaPacket/Graphics/Common/ImageData.h"
#include "TeaPacket/Graphics/GS/Texture/AvailableMode.h"
#include "TeaPacket/Graphics/GS/Texture/FilterMode.h"
#include "TeaPacket/Graphics/GS/Texture/WrapMode.h"
#include "TeaPacket/Types/Numeric.h"

/**
 * Contains flags determining how a Texture should be used.
 */
typedef struct
{
    /**
     * Whether this Texture is to be used by a shader. Almost always TRUE.
     */
    tp_bfint shaderResource : 1;
    /**
     * Whether this Texture should be readable by the CPU. Reccomended default is FALSE.
     */
    tp_bfint cpuReadable : 1;
    /**
     * The write accessibility of the Texture.
     */
    tp_bfint_t(TP_GfxGS_Texture_AvailableMode) writeMode : 2;
} TP_GfxGS_TextureUseFlags;

/**
 * Contains parameters for determining how a Texture should be created.
 */
typedef struct
{
    TP_Gfx_ImageData imageData;
    /**
     * How the texture is filtered when sampled from.
     */
    TP_GfxGS_Texture_FilterMode filterMode;
    /**
     * How the texture is sampled from when UVs are out of the 0-1 range.
     */
    TP_GfxGS_Texture_WrapMode wrapMode;
    /**
     * Flags determining how the texture should be used.
     */
    TP_GfxGS_TextureUseFlags flags;
} TP_GfxGS_TextureParams;


#endif
