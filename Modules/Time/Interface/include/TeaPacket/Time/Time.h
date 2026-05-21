/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_TIME_H
#define TEAPACKET_TIME_H
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

/**
 * Gets the current time in seconds.
 * @return The current time, in seconds, rounded down.
 */
tp_timeunit TP_Time_GetSeconds(void);
/**
 * Gets the current time in milliseconds.
 * @return The current time, in milliseconds, rounded down.
 */
tp_timeunit TP_Time_GetMilliseconds(void);
/**
 * Gets the current time in microseconds.
 * @return The current time, in microseconds, rounded down.
 */
tp_timeunit TP_Time_GetMicroseconds(void);

/**
 * Gets the current time in seconds.
 * @return The currrent time, in seconds, as a float.
 */
float TP_Time_GetSecondsF(void);
/**
 * Gets the current time in seconds.
 * @return The currrent time, in seconds, as a double.
 */
double TP_Time_GetSecondsD(void);


#ifdef __cplusplus
}
#endif
#endif
