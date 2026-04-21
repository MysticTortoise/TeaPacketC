#include "TeaPacket/Time/Time.h"

#include <coreinit/time.h>



tp_bool TP_Time_Init(void){return tp_true;}
void TP_Time_DeInit(void) {}



tp_timeunit TP_Time_GetSeconds(void)
{
    return OSTicksToSeconds(OSGetTime());
}

tp_timeunit TP_Time_GetMilliseconds(void)
{
    return OSTicksToMilliseconds(OSGetTime());
}
tp_timeunit TP_Time_GetMicroseconds(void)
{
    return OSTicksToMicroseconds(OSGetTime());
}

float TP_Time_GetSecondsF(void)
{
    return OSTicksToMicroseconds(OSGetTime()) * 1e-6f;
}

double TP_Time_GetSecondsD(void)
{
    return OSTicksToNanoseconds(OSGetTime()) * 1e-9;
}
