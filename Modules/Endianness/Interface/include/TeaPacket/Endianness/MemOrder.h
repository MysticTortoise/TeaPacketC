#ifndef TEAPACKET_ENDIAN_MEMORDER_H
#define TEAPACKET_ENDIAN_MEMORDER_H

#include "TeaPacket/Endianness/EndiannessTypes.h"

#if TP_ENDIAN_NATIVE == TP_ENDIAN_BIG

#define TP_U16_MEMORDER(a,b) 0x##a##b
#define TP_U32_MEMORDER(a,b,c,d) 0x##a##b##c##d
#define TP_U64_MEMORDER(a,b,c,d,e,f,g,h) 0x##a##b##c##d##e##f##g##h
#define TP_U16_MEMORDERB(a,b) 0b##a##b
#define TP_U32_MEMORDERB(a,b,c,d) 0b##a##b##c##d
#define TP_U64_MEMORDERB(a,b,c,d,e,f,g,h) 0b##a##b##c##d##e##f##g##h

#elif TP_ENDIAN_NATIVE == TP_ENDIAN_LITTLE

#define TP_U16_MEMORDER(a,b) 0x##b##a
#define TP_U16_MEMORDERB(a,b) 0b##b##a
#define TP_U32_MEMORDER(a,b,c,d) 0x##d##c##b##a
#define TP_U32_MEMORDERB(a,b,c,d) 0b##d##c##b##a
#define TP_U64_MEMORDER(a,b,c,d,e,f,g,h) 0x##h##g##f##e##d##c##b##a
#define TP_U64_MEMORDERB(a,b,c,d,e,f,g,h) 0b##h##g##f##e##d##c##b##a

#endif



#endif