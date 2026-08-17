#ifndef TEAPACKET_ENDIANNESS_FLOATING_H
#define TEAPACKET_ENDIANNESS_FLOATING_H

#define TP_ENDIAN_DEF_NO_REMOVE 1
#include "TeaPacket/Endianness/Conversions.h"
#include "TeaPacket/Types/Float32.h"
#include "TeaPacket/Types/Double64.h"



#ifdef __cplusplus
extern "C"
{
#endif

#if TP_SUPPORT_U32
TP_INLINE_FUNC tp_u32 TP_SwapF32(const tp_ff32 x)
{
    const tp_u32 reinterp = *(tp_u32*)&x;
    return TP_SwapU32(reinterp);
}

#if TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE
TP_INLINE_FUNC tp_u32 TP_MakeF32BigEndian(const tp_ff32 x) { return TP_SwapF32(x); }
TP_INLINE_FUNC tp_u32 TP_MakeF32LittleEndian(const tp_ff32 x)
{
    const tp_u32 reinterp = *(tp_u32*)&x;
    return reinterp;
}
#elif TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
TP_INLINE_FUNC tp_u32 TP_MakeF32LittleEndian(const tp_ff32 x) { return TP_SwapF32(x); }
TP_INLINE_FUNC tp_u32 TP_MakeF32BigEndian(const tp_ff32 x)
{
    const tp_u32 reinterp = *(tp_u32*)&x;
    return reinterp;
}
#endif

TP_INLINE_FUNC tp_u32 TP_FromF32BigEndian(const tp_ff32 x) { return TP_MakeF32BigEndian(x); }
TP_INLINE_FUNC tp_u32 TP_FromF32LittleEndian(const tp_ff32 x) { return TP_MakeF32LittleEndian(x); }
#endif



#if TP_SUPPORT_U64
TP_INLINE_FUNC tp_u64 TP_SwapD64(const tp_fd64 x)
{
    const tp_u64 reinterp = *(tp_u64*)&x;
    return TP_SwapU64(reinterp);
}

#if TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE
TP_INLINE_FUNC tp_u64 TP_MakeD64BigEndian(const tp_fd64 x) { return TP_SwapD64(x); }
TP_INLINE_FUNC tp_u64 TP_MakeD64LittleEndian(const tp_fd64 x)
{
    const tp_u64 reinterp = *(tp_u64*)&x;
    return reinterp;
}
#elif TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
TP_INLINE_FUNC tp_u64 TP_MakeD64LittleEndian(const tp_fd64 x) { return TP_SwapD64(x); }
TP_INLINE_FUNC tp_u64 TP_MakeD64BigEndian(const tp_fd64 x)
{
    const tp_u64 reinterp = *(tp_u64*)&x;
    return reinterp;
}
#endif

TP_INLINE_FUNC tp_u64 TP_FromD64BigEndian(const tp_fd64 x) { return TP_MakeD64BigEndian(x); }
TP_INLINE_FUNC tp_u64 TP_FromD64LittleEndian(const tp_fd64 x) { return TP_MakeD64LittleEndian(x); }
#endif

#ifdef __cplusplus
}
#endif
#endif
