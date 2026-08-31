/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains all parameters used in the creation of a Viewport.
 */
#ifndef TEAPACKET_TEAPACKET_GRAPHICS_GS_VIEWPORTPARAMETERS_H
#define TEAPACKET_TEAPACKET_GRAPHICS_GS_VIEWPORTPARAMETERS_H

#include "TeaPacket/Types/Numeric.h"

typedef struct
{
    /**
     * The width of the Viewport, in pixels.
     */
    tp_u16 width;
    /**
     * The height of the Viewport, in pixels.
     */
    tp_u16 height;
    /**
     * Whether this Viewport can be used as texture input to a Shader. Usually TRUE.
     */
    tp_bool shaderUsable;

} TP_GfxGS_ViewportParams;

#endif