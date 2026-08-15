/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_MACROS_FEATURES_H
#define TEAPACKET_MACROS_FEATURES_H
#ifdef __cplusplus
extern "C" {
#endif

#define TP_STRINGTOKEN2(a) TP_STRINGTOKEN(a)
#define TP_STRINGTOKEN(a) #a

#define TP_TOKENPASTE2(a, b) TP_TOKENPASTE(a, b)
#define TP_TOKENPASTE(a, b) a ## b



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

/* C++ VERSION */
#define TP_CPP_VERNONE 0L
#define TP_CPP_VER98 199711L
#define TP_CPP_VER11 201103L
#define TP_CPP_VER14 201402L
#define TP_CPP_VER17 201703L
#define TP_CPP_VER20 202002L
#define TP_CPP_VER23 202302L

#ifdef __cplusplus
#define TP_CPP_VER __cplusplus
#else
#define TP_CPP_VER TP_CPP_VERNONE
#endif

/* Compile specifics */
#if defined(__GNUC__)
#define TP_HAS_GNUC 1
#endif

#if defined(_MSC_VER)
#define TP_HAS_MSC 1
#endif

#if defined(_WIN32)
#define TP_HAS_WINDOWS 1
#endif

#if defined(__WUT__) || defined(__WIIU__)
#define TP_HAS_WIIU 1
#endif



/* inline keyword support */
#if defined(__cplusplus)
#define TP_INLINE_FUNC inline
#elif TP_C_VER >= TP_C_VER95
#define TP_INLINE_FUNC static inline
#elif defined(__GNUC__) || defined(__inline__) /* use GCC inline macro */
#define TP_INLINE_FUNC static __inline__
#elif defined(_MSC_VER) /* use MSVC inline macro */
#define TP_INLINE_FUNC __inline
#else /* Make inline function static and pray it works just fine and is actually inlined.  */
#define TP_INLINE_FUNC static
#endif

/* static_assert support */
#if TP_CPP_VER >= TP_CPP_VER11 || TP_C_VER >= TP_C_VER11
#   include <assert.h>
#   define TP_STATIC_ASSERT(condition, message, prename) static_assert(condition, message)

#else

#   define TP_STATIC_ASSERT(condition, message, prename) enum { \
    TP_TOKENPASTE2(TP_TOKENPASTE2(TP_ASSERT_line_, __LINE__), prename) = 1 / (message && (condition))}

#endif


#ifdef __cplusplus
}
#endif
#endif