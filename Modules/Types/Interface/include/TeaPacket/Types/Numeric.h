#ifndef TEAPACKET_TYPES_NUMERIC_H
#define TEAPACKET_TYPES_NUMERIC_H

#include "TeaPacket/MacroUtils/Features.h"
#include "limits.h"

typedef unsigned char tp_byte;

/* BOOLS =========================================== */
#if TP_C_VER >= TP_C_VER99
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
#if TP_C_VER >= TP_C_VER99
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
/* <=C95 - WE GOTTA FAKE IT :D*/

/* 8 bit int */
#if CHAR_BIT == 8
#define TP_SUPPORT_U8 1
typedef unsigned char tp_u8;
#define TP_SUPPORT_I8 1
typedef signed char tp_i8;
#endif

/* SIGNED INTS =========================================================== */

/* i16 */
#if SHRT_MAX == 32767
#define TP_SUPPORT_I16 1
typedef signed short tp_i16;
#elif INT_MAX == 32767
#define TP_SUPPORT_I16 1
typedef signed int tp_i16;
#elif LONG_MAX == 32767
#define TP_SUPPORT_I16 1
typedef signed long tp_i16;
#endif

/* i32 */
#if SHRT_MAX == 2147483647
#define TP_SUPPORT_I32 1
typedef signed short tp_i32;
#elif INT_MAX == 2147483647
#define TP_SUPPORT_I32 1
typedef signed int tp_i32;
#elif LONG_MAX == 2147483647
#define TP_SUPPORT_I32 1
typedef signed long tp_i32;
#endif

/* i64 */
#if SHRT_MAX == 9223372036854775807UL /* todo: does this even work? */
#define TP_SUPPORT_I64 1
typedef signed short tp_i64;
#elif INT_MAX == 9223372036854775807UL
#define TP_SUPPORT_I64 1
typedef signed int tp_i64;
#elif LONG_MAX == 9223372036854775807UL
#define TP_SUPPORT_I64 1
typedef signed long tp_i64;
#endif

/* UNSIGNED INTS =========================================================== */

/* u16 */
#if USHRT_MAX == 65535
#define TP_SUPPORT_U16 1
typedef unsigned short tp_u16;
#elif UINT_MAX == 65535
#define TP_SUPPORT_U16 1
typedef unsigned int tp_u16;
#elif ULONG_MAX == 65535
#define TP_SUPPORT_U16 1
typedef unsigned long tp_u16;
#endif

/* u32 */
#if USHRT_MAX == 4294967295
#define TP_SUPPORT_U32 1
typedef unsigned short tp_u32;
#elif UINT_MAX == 4294967295
#define TP_SUPPORT_U32 1
typedef unsigned int tp_u32;
#elif ULONG_MAX == 4294967295
#define TP_SUPPORT_U32 1
typedef unsigned long tp_u32;
#endif

/* u64 */
#if USHRT_MAX == 18446744073709551615UL
#define TP_SUPPORT_U64 1
typedef unsigned short tp_u64;
#elif UINT_MAX == 18446744073709551615UL
#define TP_SUPPORT_U64 1
typedef unsigned int tp_u64;
#elif ULONG_MAX == 18446744073709551615UL
#define TP_SUPPORT_U64 1
typedef unsigned long tp_u64;
#endif

#endif /* ENDIF C90*/


#endif