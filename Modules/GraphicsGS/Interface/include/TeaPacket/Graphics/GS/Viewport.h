/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Viewports are textures that can be rendered to.
 * Viewports are Displays, separated from the requirement of being visible to the user.
 */
#ifndef TEAPACKET_GRAPHICS_GS_VIEWPORT_H
#define TEAPACKET_GRAPHICS_GS_VIEWPORT_H

#include "TeaPacket/Graphics/GS/ViewportParams.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_GfxGS_Viewport TP_GfxGS_Viewport;

/**
 * Creates a Viewport from the given parameters.
 * @param params The parameters to create this Viewport with.
 * @return The created Viewport.
 */
TP_GfxGS_Viewport* TP_GfxGS_Viewport_Create(const TP_GfxGS_ViewportParams* params);
/**
 * Destroys a Viewport.
 */
void TP_GfxGS_Viewport_Destroy(const TP_GfxGS_Viewport*);

/**
 * Sets this Viewport to be the current active target for rendering.
 * @details Any calls to this function must be followed by a call to TP_GfxGS_Viewport_FinishRender.
 * @warning This conflicts with TP_GfxGS_Display_BeginRender. Only have one active target at a time.
 *
 * Calling this function multiple times without calling TP_GfxGS_Viewport_FinishRender is undefined behavior.
 * @param viewport The Viewport to be targeted.
 */
void TP_GfxGS_Viewport_BeginRender(TP_GfxGS_Viewport* viewport);
/**
 * Finishes rendering the current Viewport..
 * @details This function must be preceded with a call to TP_GfxGS_Viewport_BeginRender.
 * @warning Calling this function without a prior call to TP_GfxGS_Viewport_BeginRender,
 * or after another call to TP_GfxGS_Viewport_FinishRender, is undefined behavior.
 */
void TP_GfxGS_Viewport_FinishRender(void);

/**
 * Gets the width of a Viewport.
 * @return The width of the Viewport, in pixels.
 */
tp_u16 TP_GfxGS_Viewport_GetWidth(TP_GfxGS_Viewport*);
/**
 * Gets the height of a Viewport.
 * @return The height of the Viewport, in pixels.
 */
tp_u16 TP_GfxGS_Viewport_GetHeight(TP_GfxGS_Viewport*);

#ifdef __cplusplus
}
#endif
#endif
