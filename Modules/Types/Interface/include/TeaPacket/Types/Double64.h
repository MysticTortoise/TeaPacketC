#ifndef TEAPACKET_TYPES_DOUBLEFIXED_H
#define TEAPACKET_TYPES_DOUBLEFIXED_H

#include <limits.h>
#include "TeaPacket/MacroUtils/Features.h"


TP_STATIC_ASSERT(64 == sizeof(double) * CHAR_BIT, __FILE__ " should not be included when size of double is not 64 bits",
    types_doublefixed_h);
typedef double tp_fd64;

#endif
