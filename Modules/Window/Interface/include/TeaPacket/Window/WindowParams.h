
#ifndef TEAPACKET_WINDOW_PARAMS_H
#define TEAPACKET_WINDOW_PARAMS_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    tp_u16 x;
    tp_u16 y;
    tp_u16 width;
    tp_u16 height;

    TP_StringView title;
} TP_Window_Params;

#ifdef __cplusplus
}
#endif
#endif
