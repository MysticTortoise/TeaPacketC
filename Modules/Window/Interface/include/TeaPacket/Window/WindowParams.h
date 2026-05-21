/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used to create a Window.
 */
#ifndef TEAPACKET_WINDOW_PARAMS_H
#define TEAPACKET_WINDOW_PARAMS_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    /**
     * The initial X position of a Window.
     */
    tp_u16 x;
    /**
     * The initial Y position of a Window.
     */
    tp_u16 y;
    /**
     * The initial width of a Window.
     */
    tp_u16 width;
    /**
     * The initial height of a Window.
     */
    tp_u16 height;

    /**
     * The initial title of a Window.
     */
    TP_StringView title;
} TP_Window_Params;

#ifdef __cplusplus
}
#endif
#endif
