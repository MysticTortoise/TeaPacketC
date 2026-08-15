/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_ENDIAN_ENDIANNESSTYPES_H
#define TEAPACKET_ENDIAN_ENDIANNESSTYPES_H

/* NATIVE ENDIAN SET */
#define TP_ENDIAN_BIG 0x04030201UL
#define TP_ENDIAN_LITTLE 0x01020304UL

/* PLATFORM SPECIFICS */
/* CMAKE will try and define a TP_ENDIAN_NATIVE macro - if fails, these will try and figure it out. */

/* WINDOWS ENDIAN CHECK */
#if !defined(TP_ENDIAN_NATIVE) && defined(TP_HAS_WINDOWS)
#   include <Windows.h>

#   if REG_DWORD == REG_DWORD_LITTLE_ENDIAN
#       define TP_ENDIAN_NATIVE TP_ENDIAN_LITTLE
#   elif REG_DWORD == REG_DWORD_BIG_ENDIAN
#       define TP_ENDIAN_NATIVE TP_ENDIAN_BIG
#   endif
#endif

/* WIIU ENDIAN CHECK */
#if !defined(TP_ENDIAN_NATIVE) && defined(TP_HAS_WIIU)
#define TP_ENDIAN_NATIVE TP_ENDIAN_BIG
#endif



/* GCC / CLANG / OTHER */
#if !defined(TP_ENDIAN_NATIVE) && defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && defined(__ORDER_LITTLE_ENDIAN__)
#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       define TP_ENDIAN_NATIVE TP_ENDIAN_LITTLE
#   elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       define TP_ENDIAN_NATIVE TP_ENDIAN_BIG
#   endif
#endif


#endif