/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/*
 * Windows represet a Window on a desktop platform. While they also function as TP_Graphics_Display objects,
 * that functionality should be accessed via the Graphics Module and not here.
 *
 * Windows are created here instead of through the Graphics API.
 */
#ifndef TEAPACKET_WINDOW_H
#define TEAPACKET_WINDOW_H

#include "TeaPacket/Window/WindowParams.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TP_Window TP_Window;

/**
 * Creates a Window with the given parameters.
 * @param params The parameters to create the Window with.
 * @return The created Window.
 */
TP_Window* TP_Window_Create(const TP_Window_Params* params);
/**
 * Destroys a window.
 */
void TP_Window_Destroy(TP_Window*);

/**
 * Process all events relating to a Window. On many platforms, this is called by the System module.
 */
void TP_Window_ProcessEvents(TP_Window*);

/**
 * Gets the current amount of Windows active.
 * @return The amount of Windows currently active.
 */
size_t TP_Window_GetCount(void);
/**
 * Gets a Window by its index.
 * @param index The index of the Window to get.
 * @return The Window with that index.
 */
TP_Window* TP_Window_Get(size_t index);

tp_u16 TP_Window_GetXPos(TP_Window*);
tp_u16 TP_Window_GetYPos(TP_Window*);
tp_u16 TP_Window_GetWidth(TP_Window*);
tp_u16 TP_Window_GetHeight(TP_Window*);

/**
 * Gets the title of a Window.
 *
 * The title of a Window typically appears on a bar above the Window itself.
 * @return The title of the Window.
 */
TP_String TP_Window_GetTitle(TP_Window*);

void TP_Window_SetXPos(TP_Window*, tp_u16 xPos);
void TP_Window_SetYPos(TP_Window*, tp_u16 yPos);
void TP_Window_SetWidth(TP_Window*, tp_u16 width);
void TP_Window_SetHeight(TP_Window*, tp_u16 height);

/**
 * Sets a Window's title.
 * @param name The new title of the Window.
 */
void TP_Window_SetTitle(TP_Window*, TP_StringView name);

/**
 * Gets a Window's ID.
 * @return The ID used by this Window. Will match the Display ID of the Window.
 */
tp_u16 TP_Window_GetID(const TP_Window*);

#ifdef __cplusplus
}
#endif
#endif
