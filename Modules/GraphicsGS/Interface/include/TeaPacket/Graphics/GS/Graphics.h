/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Contains functions for Graphics not tied to any one object.
 * Primarily contains drawing functions.
 */
#ifndef TEAPACKET_GRAPHICS_GS_H
#define TEAPACKET_GRAPHICS_GS_H

#include "TeaPacket/Graphics/Common/Color.h"
#include "TeaPacket/Types/Numeric.h"


#ifdef __cplusplus
extern "C" {
#endif


tp_bool TP_GraphicsGS_Init(void);
void TP_GraphicsGS_DeInit(void);

/**
 * Draws a mesh based on the current state of the Graphics Module.
 * @details This is based on the currently active Mesh, Shader, ShaderBuffers, Viewport, and other data.
 */
void TP_GfxGS_DrawMesh(void);


/**
 * Clears the currently active Viewport with a color. Will also clear its depth buffer if possible.
 * @param clearColor The color to clear the viewport with.
 */
void TP_GfxGS_ClearColor(TP_Gfx_Color8 clearColor);

/**
 * Enables or disables depth testing for the entire Module. If depth testing is disabled, meshes drawn later will render over meshes drawn first.
 * @param depthEnabled Whether to enable depth or not.
 */
void TP_GfxGS_SetDepthEnabled(tp_bool depthEnabled);

#ifdef __cplusplus
}
#endif
#endif
