/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the request to create a Display.
 */
#ifndef TEAPACKET_TEAPACKET_GRAPHICS_DISPLAYPARAMETERS_H
#define TEAPACKET_TEAPACKET_GRAPHICS_DISPLAYPARAMETERS_H

#include "TeaPacket/Types/Numeric.h"

/**
 * All parameters used in the request to create a Display.
 */
typedef struct
{
    /**
     * The suggested width of the Display.
     */
    tp_u16 width;
    /**
     * The suggested height of the Display.
     */
    tp_u16 height;
} TP_Graphics_DisplayParams;

#endif
