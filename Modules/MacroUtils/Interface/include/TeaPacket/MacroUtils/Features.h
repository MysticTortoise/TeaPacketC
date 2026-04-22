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


#ifndef __STDC_VERSION__
#define TP_C_VER TP_C_VER90
#else
#define TP_C_VER __STDC_VERSION__
#endif



#if TP_C_VER >= TP_C_VER95
#define TP_SUPPORT_INLINE 1
#define TP_INLINE_FUNC inline
#elif defined(__GNUC__)
#define TP_INLINE_FUNC inline
#else
#define TP_INLINE_FUNC static
#endif


#ifdef __cplusplus
}
#endif
#endif