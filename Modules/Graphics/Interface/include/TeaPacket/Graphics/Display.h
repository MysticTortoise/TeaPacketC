/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Displays are screens displayed to the user. They act as a Viewport that the user can see, and usually map to some kind of physical display.
 *
 * The standard for implementing Displays is to have them represent a screen on typical devices,
 * and represent a Window on Desktop-based devices.
 */
#ifndef TEAPACKET_GRAPHICS_DISPLAY_H
#define TEAPACKET_GRAPHICS_DISPLAY_H

#include "TeaPacket/Graphics/DisplayParams.h"
#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TP_Graphics_Display TP_Graphics_Display;

typedef TP_ArrayView(TP_Graphics_DisplayParams) TP_Graphics_DisplayParamList;

typedef tp_u16 TP_Graphics_DisplayID;


/**
 * Initializes the Displays wanted by your application. This MUST be called before any Display-based graphics operations begin.
 * @param params A list of parameters you would like each Display to use, ordered by Display ID. The implementation will choose the closest option to what you have requested.
 */
void TP_Graphics_InitDefaultDisplays(TP_Graphics_DisplayParamList params);
/**
 * Gets the amount of Displays currently available.
 * @return The amount of Displays available. The highest accessible Display is this ID-1
 */
TP_Graphics_DisplayID TP_Graphics_Display_GetCount(void);


/**
 * Sets this Display to be the current active target for rendering.
 * @details Any calls to this function must be followed by a call to TP_Graphics_Display_FinishRender.
 * @warning This conflicts with TP_Graphics_Viewport_BeginRender. Only have one active target at a time.
 *
 * Calling this function multiple times without calling TP_Graphics_Display_FinishRender is undefined behavior.
 * @param id The ID of the Display that will be targeted.
 */
void TP_Graphics_Display_BeginRender(TP_Graphics_DisplayID id);
/**
 * Finishes rendering the current Display.
 * @details This function must be preceded with a call to TP_Graphics_Display_BeginRender.
 * @warning Calling this function without a prior call to TP_Graphics_Display_BeginRender,
 * or after another call to TP_Graphics_Display_FinishRender, is undefined behavior.
 */
void TP_Graphics_Display_FinishRender(void);

/**
 * Gets the width of a display.
 * @param id The Display to get the width of.
 * @return The width of the display, in pixels.
 */
tp_u16 TP_Graphics_Display_GetWidth(TP_Graphics_DisplayID id);
/**
 * Gets the height of a display.
 * @param id The Display to get height width of.
 * @return The height of the display, in pixels.
 */
tp_u16 TP_Graphics_Display_GetHeight(TP_Graphics_DisplayID id);

/**
 * Updates all drawing done to a Display to be shown to the user.
 * @param waitForVSync Whether the function should halt until the vertical-blanking period of the Display is finished or not.
 * @details If waitForVSync is set to TRUE, then this function will halt until the frame is actually displayed.
 */
void TP_Graphics_Display_PresentAll(tp_bool waitForVSync);


#ifdef __cplusplus
}
#endif
#endif
