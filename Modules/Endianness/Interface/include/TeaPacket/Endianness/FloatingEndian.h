#ifndef TEAPACKET_ENDIANNESS_FLOATING_H
#define TEAPACKET_ENDIANNESS_FLOATING_H

#define TP_ENDIAN_DEF_NO_REMOVE
#include "TeaPacket/Endianness/Conversions.h"
#include "TeaPacket/Endianness/Endian.h"
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
TP_ENDIAN_DEF(ff32,F32)
#endif

#if TP_SUPPORT_U64
TP_INLINE_FUNC tp_u64 TP_SwapD64(const tp_fd64 x)
{
    const tp_u64 reinterp = *(tp_u64*)&x;
    return TP_SwapU64(reinterp);
}
TP_ENDIAN_DEF(fd64,D64)
#endif


#undef TP_ENDIAN_DEF
#undef TP_ENDIAN_DEF_MAKE_BIG
#undef TP_ENDIAN_DEF_MAKE_LITTLE
    
#ifdef __cplusplus
}
#endif
#endif
