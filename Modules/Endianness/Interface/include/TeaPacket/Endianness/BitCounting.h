#ifndef TEAPACKET_ENDIAN_BITCOUNTING_H
#define TEAPACKET_ENDIAN_BITCOUNTING_H

#include <assert.h>

#include "TeaPacket/Types/Numeric.h"

#if TP_CPP_VER >= TP_CPP_VER20
#include <bit>
#elif TP_C_VER >= TP_C_VER23
#include "stdlib.h"
#elif TP_HAS_MSC
#include <intrin.h>
#endif


#ifdef __cplusplus
extern "C"
{
#endif


TP_INLINE_FUNC tp_u8 TP_Bit_CountTrailingZeros(tp_u32 x)
{
    assert(x != 0);
#if TP_CPP_VER >= TP_CPP_VER20
    return (tp_u8)std::countr_zero(x);
#elif defined(TP_HAS_GNUC)
    return (tp_u8)__builtin_ctz(x);
#elif TP_C_VER >= TP_C_VER23
    return (tp_u8)stdc_trailing_zeros(x);
#elif TP_HAS_MSC 
    unsigned long y;
    _BitScanForward(&y, x);
    return (tp_u8)y;
#else
    unsigned int v;      /* 32-bit word input to count zero bits on right */
    unsigned int c = 32; /* c will be the number of zero bits on the right */
    v &= -(signed int)v;
    if (v) c--;
    if (v & 0x0000FFFF) c -= 16;
    if (v & 0x00FF00FF) c -= 8;
    if (v & 0x0F0F0F0F) c -= 4;
    if (v & 0x33333333) c -= 2;
    if (v & 0x55555555) c -= 1;
    return c;
#endif
}


#ifdef __cplusplus
}
#endif
#endif
