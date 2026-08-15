/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_ENDIAN_CONVERSIONS_H
#define TEAPACKET_ENDIAN_CONVERSIONS_H

#include "TeaPacket/Endianness/EndiannessTypes.h"
#include "TeaPacket/Endianness/Swapping.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE
#define TP_ENDIAN_DEF_MAKE_BIG(typename, type) TP_INLINE_FUNC tp_##typename TP_Make##type##BigEndian(const tp_##typename x) \
    { return TP_Swap##type(x); }
#elif TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
#define TP_ENDIAN_DEF_MAKE_BIG(typename, type) TP_INLINE_FUNC tp_##typename TP_Make##type##BigEndian(const tp_##typename x) \
{ return x; }
#endif

#if TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
#define TP_ENDIAN_DEF_MAKE_LITTLE(typename, type) TP_INLINE_FUNC tp_##typename TP_Make##type##LittleEndian(const tp_##typename x) \
{ return TP_Swap##type(x); }
#elif TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE
#define TP_ENDIAN_DEF_MAKE_LITTLE(typename, type) TP_INLINE_FUNC tp_##typename TP_Make##type##LittleEndian(const tp_##typename x) \
{ return x; }
#endif

#define TP_ENDIAN_DEF(typename, type) \
    TP_ENDIAN_DEF_MAKE_BIG(typename, type) \
    TP_ENDIAN_DEF_MAKE_LITTLE(typename, type) \
    TP_INLINE_FUNC tp_##typename TP_From##type##BigEndian(const tp_##typename x) { return TP_Make##type##BigEndian(x); } \
    TP_INLINE_FUNC tp_##typename TP_From##type##LittleEndian(const tp_##typename x) { return TP_Make##type##LittleEndian(x); } \

#if TP_SUPPORT_U16
TP_ENDIAN_DEF(u16, U16)
#endif
#if TP_SUPPORT_I16
TP_ENDIAN_DEF(i16, I16)
#endif
#if TP_SUPPORT_U32
TP_ENDIAN_DEF(u32, U32)
#endif
#if TP_SUPPORT_I32
TP_ENDIAN_DEF(i32, I32)
#endif
#if TP_SUPPORT_U64
TP_ENDIAN_DEF(u64, U64)
#endif
#if TP_SUPPORT_I64
TP_ENDIAN_DEF(i64, I64)
#endif



#ifndef TP_ENDIAN_DEF_NO_REMOVE
#undef TP_ENDIAN_DEF
#undef TP_ENDIAN_DEF_MAKE_BIG
#undef TP_ENDIAN_DEF_MAKE_LITTLE
#endif
    
#ifdef __cplusplus
}
#endif
#endif
