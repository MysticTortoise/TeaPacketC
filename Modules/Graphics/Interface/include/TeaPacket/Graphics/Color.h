#ifndef TEAPACKET_GRAPHICS_COLOR_H
#define TEAPACKET_GRAPHICS_COLOR_H

#include "TeaPacket/Types/Numeric.h"
#include "TeaPacket/Types/Array.h"


typedef struct
{
    tp_u8 r;
    tp_u8 g;
    tp_u8 b;
} TP_Graphics_Color8;

typedef struct
{
    tp_u8 r;
    tp_u8 g;
    tp_u8 b;
    tp_u8 a;
} TP_Graphics_Color8A;

typedef TP_Array(TP_Graphics_Color8A) TP_Graphics_Color8A_List;
typedef TP_Array(TP_Graphics_Color8) TP_Graphics_Color8_List;

#endif