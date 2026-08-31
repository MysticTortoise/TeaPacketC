/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_TYPES_NUMERIC_H
#define TEAPACKET_TYPES_NUMERIC_H

#include "TeaPacket/MacroUtils/Features.h"
#include "limits.h"

typedef unsigned char tp_byte;

/* BOOLS =========================================== */
#if TP_C_VER >= TP_C_VER99 || defined(__cplusplus)
#include <stdbool.h>
typedef bool tp_bool;
#define tp_false false
#define tp_true true
#else
typedef unsigned char tp_bool;
#define tp_false 0
#define tp_true 1
#endif

/* FIXED WIDTH INTS ================================ */
#define TP_MAXI8 127UL
#define TP_MAXU8 255UL

#define TP_MAXI16 32767UL
#define TP_MAXU16 65535UL

#define TP_MAXI32 2147483647UL
#define TP_MAXU32 4294967295UL

#define TP_MAX_I64 9223372036854775807UL
#define TP_MAX_U64 18446744073709551615UL

#if TP_C_VER >= TP_C_VER99 || __cplusplus >= 201103L
#include "stdint.h"
#define TP_SUPPORT_U8 1
typedef uint8_t tp_u8;
#define TP_SUPPORT_I8 1
typedef int8_t tp_i8;
#define TP_SUPPORT_U16 1
typedef uint16_t tp_u16;
#define TP_SUPPORT_I16 1
typedef int16_t tp_i16;
#define TP_SUPPORT_U32 1
typedef uint32_t tp_u32;
#define TP_SUPPORT_I32 1
typedef int32_t tp_i32;
#define TP_SUPPORT_U64 1
typedef uint64_t tp_u64;
#define TP_SUPPORT_I64 1
typedef int64_t tp_i64;

#else

/* MSVC SPECIFIC INT SIZES */
#ifdef TP_HAS_MSC

#define TP_SUPPORT_U8 1
typedef unsigned __int8 tp_u8;
#define TP_SUPPORT_I8 1
typedef __int8 tp_i8;
#define TP_SUPPORT_U16 1
typedef unsigned __int16 tp_u16;
#define TP_SUPPORT_I16 1
typedef __int16 tp_i16;
#define TP_SUPPORT_U32 1
typedef unsigned __int32 tp_u32;
#define TP_SUPPORT_I32 1
typedef __int32 tp_i32;
#define TP_SUPPORT_U64 1
typedef unsigned __int64 tp_u64;
#define TP_SUPPORT_I64 1
typedef __int64 tp_i64;

#else

/* <C99 - WE GOTTA FAKE IT :D*/


/* 8 bit int */
#if CHAR_BIT == 8
#define TP_SUPPORT_U8 1
typedef unsigned char tp_u8;
#define TP_SUPPORT_I8 1
typedef signed char tp_i8;
#endif

/* SIGNED INTS =========================================================== */

/* i16 */
#if SHRT_MAX == TP_MAXI16
#define TP_SUPPORT_I16 1
typedef signed short tp_i16;
#elif INT_MAX == TP_MAXI16
#define TP_SUPPORT_I16 1
typedef signed int tp_i16;
#elif LONG_MAX == TP_MAXI16
#define TP_SUPPORT_I16 1
typedef signed long tp_i16;
#endif

/* i32 */
#if SHRT_MAX == TP_MAXI32
#define TP_SUPPORT_I32 1
typedef signed short tp_i32;
#elif INT_MAX == TP_MAXI32
#define TP_SUPPORT_I32 1
typedef signed int tp_i32;
#elif LONG_MAX == TP_MAXI32
#define TP_SUPPORT_I32 1
typedef signed long tp_i32;
#endif

/* i64 */
#if SHRT_MAX == TP_MAX_I64 /* todo: does this even work? */
#define TP_SUPPORT_I64 1
typedef signed short tp_i64;
#elif INT_MAX == TP_MAX_I64
#define TP_SUPPORT_I64 1
typedef signed int tp_i64;
#elif LONG_MAX == TP_MAX_I64
#define TP_SUPPORT_I64 1
typedef signed long tp_i64;
#endif

/* UNSIGNED INTS =========================================================== */

/* u16 */
#if USHRT_MAX == TP_MAXU16
#define TP_SUPPORT_U16 1
typedef unsigned short tp_u16;
#elif UINT_MAX == TP_MAXU16
#define TP_SUPPORT_U16 1
typedef unsigned int tp_u16;
#elif ULONG_MAX == TP_MAXU16
#define TP_SUPPORT_U16 1
typedef unsigned long tp_u16;
#endif

/* u32 */
#if USHRT_MAX == TP_MAXU32
#define TP_SUPPORT_U32 1
typedef unsigned short tp_u32;
#elif UINT_MAX == TP_MAXU32
#define TP_SUPPORT_U32 1
typedef unsigned int tp_u32;
#elif ULONG_MAX == TP_MAXU32
#define TP_SUPPORT_U32 1
typedef unsigned long tp_u32;
#endif

/* u64 */
#if USHRT_MAX == TP_MAX_U64
#define TP_SUPPORT_U64 1
typedef unsigned short tp_u64;
#elif UINT_MAX == TP_MAX_U64
#define TP_SUPPORT_U64 1
typedef unsigned int tp_u64;
#elif ULONG_MAX == TP_MAX_U64
#define TP_SUPPORT_U64 1
typedef unsigned long tp_u64;
#elif defined(TP_HAS_GNUC)
#define TP_SUPPORT_U64 1
__extension__ typedef unsigned long long int tp_u64;
#endif

#endif

#endif /* ENDIF C90*/


typedef unsigned int tp_bfint;

#define tp_bfint_t(trueType) tp_bfint

#endif