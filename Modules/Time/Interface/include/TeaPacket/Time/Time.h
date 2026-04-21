
#ifndef TEAPACKET_RANDOM_STDRANDOM_TIME_H
#define TEAPACKET_RANDOM_STDRANDOM_TIME_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Types/Numeric.h"

tp_bool TP_Time_Init(void);
void TP_Time_DeInit(void);

#ifdef TP_SUPPORT_U64
typedef tp_u64 tp_timeunit;
#else
typedef tp_u32 tp_timeunit;
#endif

tp_timeunit TP_Time_GetSeconds(void);
tp_timeunit TP_Time_GetMilliseconds(void);
tp_timeunit TP_Time_GetMicroseconds(void);

float TP_Time_GetSecondsF(void);
double TP_Time_GetSecondsD(void);


#ifdef __cplusplus
}
#endif
#endif
