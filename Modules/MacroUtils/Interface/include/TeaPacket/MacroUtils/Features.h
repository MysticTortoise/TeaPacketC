/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_MACROS_FEATURES_H
#define TEAPACKET_MACROS_FEATURES_H
#ifdef __cplusplus
extern "C" {
#endif


/* C VERSION */
#define TP_C_VER90 199001L
#define TP_C_VER95 199409L
#define TP_C_VER99 199901L
#define TP_C_VER11 201112L
#define TP_C_VER17 201710L
#define TP_C_VER23 202311L

/* Ensure the TP_C_VER macro is always defined in some way */
#ifndef __STDC_VERSION__
#define TP_C_VER TP_C_VER90
#else
#define TP_C_VER __STDC_VERSION__
#endif


/* inline keyword support */
#if TP_C_VER >= TP_C_VER95
#define TP_SUPPORT_INLINE 1
#define TP_INLINE_FUNC inline
#elif defined(__GNUC__) || defined(__inline__) /* use GCC inline macro */
#define TP_INLINE_FUNC __inline__
#elif defined(_MSC_VER) /* use MSVC inline macro */
#define TP_INLINE_FUNC __inline
#else /* Make inline function static and pray it works just fine and is actually inlined.  */
#define TP_INLINE_FUNC static
#endif


#ifdef __cplusplus
}
#endif
#endif