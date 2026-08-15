#ifndef TEAPACKET_TYPES_FLOATFIXED_H
#define TEAPACKET_TYPES_FLOATFIXED_H

#include <limits.h>
#include "TeaPacket/MacroUtils/Features.h"


TP_STATIC_ASSERT(32 == sizeof(float) * CHAR_BIT, __FILE__ " should not be included when size of float is not 32 bits",
    types_floatfixed_h);
typedef float tp_ff32;

#endif
