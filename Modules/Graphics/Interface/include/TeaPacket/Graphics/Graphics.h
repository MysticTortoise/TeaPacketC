/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Contains functions for Graphics not tied to any one object.
 * Primarily contains drawing functions.
 */
#ifndef TEAPACKET_GRAPHICS_H
#define TEAPACKET_GRAPHICS_H

#include "TeaPacket/Types/Numeric.h"


#ifdef __cplusplus
extern "C" {
#endif


tp_bool TP_Graphics_Init(void);
void TP_Graphics_DeInit(void);

/**
 * Draws a mesh based on the current state of the Graphics Module.
 * @details This is based on the currently active Mesh, Shader, ShaderBuffers, Viewport, and other data.
 */
void TP_Graphics_DrawMesh(void);


/**
 * Clears the currently active Viewport with a color. Will also clear its depth buffer if possible.
 * @param r The red value to clear the Viewport with, from 0-255.
 * @param g The green value to clear the Viewport with, from 0-255.
 * @param b The blue value to clear the Viewport with, from 0-255.
 */
void TP_Graphics_ClearColor(tp_u8 r,
                            tp_u8 g,
                            tp_u8 b);

/**
 * Enables or disables depth testing for the entire Module. If depth testing is disabled, meshes drawn later will render over meshes drawn first.
 * @param depthEnabled Whether to enable depth or not.
 */
void TP_Graphics_SetDepthEnabled(tp_bool depthEnabled);

#ifdef __cplusplus
}
#endif
#endif
