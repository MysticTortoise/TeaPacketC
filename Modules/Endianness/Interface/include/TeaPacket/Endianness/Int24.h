#ifndef TEAPACKET_ENDIAN_INT24_H
#define TEAPACKET_ENDIAN_INT24_H

#include <assert.h>

#include "TeaPacket/Endianness/EndiannessTypes.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C"
{
#endif


TP_INLINE_FUNC tp_u32 TP_Bit_FromU24(const tp_byte* u24ptr)
{
#if TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE
    return  ((tp_u32)u24ptr[0] << 0) |
            ((tp_u32)u24ptr[1] << 8) |
            ((tp_u32)u24ptr[2] << 16);
#elif TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
    return  ((tp_u32)u24ptr[0] << 16)|
            ((tp_u32)u24ptr[1] << 8) |
            ((tp_u32)u24ptr[2] << 0);
#else
    assert(0)
    return 0;
#endif
}



#ifdef __cplusplus
}
#endif
#endif