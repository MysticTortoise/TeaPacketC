/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Textures contain image data used in rendering.
 * A Texture alone is attached to a Shader and used within.
 */

#ifndef TEAPACKET_GRAPHICS_GS_TEXTURE_H
#define TEAPACKET_GRAPHICS_GS_TEXTURE_H

#include "TeaPacket/Graphics/GS/Texture/TextureParams.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TP_GfxGS_Texture TP_GfxGS_Texture;

/**
 * Creates a texture from a set of parameters.
 * @return The created texture.
 */
TP_GfxGS_Texture* TP_GfxGS_Texture_Create(const TP_GfxGS_TextureParams*);
/**
 * Destroys a texture.
 */
void TP_GfxGS_Texture_Destroy(TP_GfxGS_Texture*);

/**
 * Gets the width of a texture.
 * @return The texture's width, in pixels.
 */
tp_u16 TP_GfxGS_Texture_GetWidth(TP_GfxGS_Texture*);

/**
 * Gets the height of a texture.
 * @return The texture's height, in pixels.
 */
tp_u16 TP_GfxGS_Texture_GetHeight(TP_GfxGS_Texture*);

/**
 * Gets the format of a texture.
 * @return The texture's format.
 */
TP_Gfx_Image_Format TP_GfxGS_Texture_GetFormat(TP_GfxGS_Texture*);

/**
 * Binds a texture to a slot. Slots correspond to location of a texture in GLSL.
 * @param texture The texture to bind.
 * @param slot The slot to bind the texture to.
 */
void TP_GfxGS_Texture_SetActive(TP_GfxGS_Texture* texture,
                                   tp_u8 slot);

/**
 * Checks whether a Texture Format is supported by the current implementation.
 * @param format The format to check.
 * @return Whether the format is supported or not.
 */
tp_bool TP_GfxGS_Texture_IsFormatSupported(TP_Gfx_Image_Format format);

#ifdef __cplusplus
}
#endif
#endif
