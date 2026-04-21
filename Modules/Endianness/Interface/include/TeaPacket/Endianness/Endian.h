#ifndef TEAPACKET_ENDIAN_H
#define TEAPACKET_ENDIAN_H
#ifdef __cplusplus
extern "C" {

#endif

#include "TeaPacket/MacroUtils/Features.h"
#include "TeaPacket/Types/Numeric.h"
#include "stddef.h"

#if TP_SUPPORT_U16
TP_INLINE tp_u16 TP_SwapU16(tp_u16 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    return (x>>8) | (x<<8);
}
#else
;
#endif
#endif

#if TP_SUPPORT_I16
TP_INLINE tp_i16 TP_SwapI16(tp_i16 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    return (x>>8) | (x<<8);
}
#else
;
#endif
#endif

#if TP_SUPPORT_U32
TP_INLINE tp_u32 TP_SwapU32(tp_u32 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    return ((x>>24)&0xff) | ((x<<8)&0xff0000) | ((x>>8)&0xff00) | ((x<<24)&0xff000000);
}
#else
;
#endif
#endif

#if TP_SUPPORT_I32
TP_INLINE tp_i32 TP_SwapI32(tp_i32 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    return ((x>>24)&0xff) | ((x<<8)&0xff0000) | ((x>>8)&0xff00) | ((x<<24)&0xff000000);
}
#else
;
#endif
#endif

#if TP_SUPPORT_U64
TP_INLINE tp_u64 TP_SwapU64(tp_u64 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
    x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
    x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
    return x;
}
#else
;
#endif
#endif

#if TP_SUPPORT_I64
TP_INLINE tp_i64 TP_SwapI64(tp_i64 x)
#if defined(TP_SUPPORT_INLINE) || TP_DEFINE_INLINE_ENDIAN
{
    x = (x & 0x00000000FFFFFFFF) << 32 | (x & 0xFFFFFFFF00000000) >> 32;
    x = (x & 0x0000FFFF0000FFFF) << 16 | (x & 0xFFFF0000FFFF0000) >> 16;
    x = (x & 0x00FF00FF00FF00FF) << 8  | (x & 0xFF00FF00FF00FF00) >> 8;
    return x;
}
#else
;
#endif
#endif




#ifdef __cplusplus
}
#endif
#endif
