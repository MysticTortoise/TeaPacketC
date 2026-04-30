
#ifndef TEAPACKET_TEAPACKET_GRAPHICS_VIEWPORTPARAMETERS_H
#define TEAPACKET_TEAPACKET_GRAPHICS_VIEWPORTPARAMETERS_H

#include "TeaPacket/Types/Numeric.h"

typedef struct
{
    tp_u16 width;
    tp_u16 height;
    tp_bool shaderUsable;

} TP_Graphics_ViewportParams;

#endif