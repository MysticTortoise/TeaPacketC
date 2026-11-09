#include "TeaPacket/Time/Time.h"

#import <QuartzCore/QuartzCore.h>

tp_bool TP_Time_Init(void)
{
    return tp_true;
}

void TP_Time_DeInit(void)
{

}

tp_timeunit TP_Time_GetSeconds(void)
{
    return (tp_timeunit)CACurrentMediaTime();
}

tp_timeunit TP_Time_GetMilliseconds(void)
{
    return (tp_timeunit)(CACurrentMediaTime() * 1000);
}

tp_timeunit TP_Time_GetMicroseconds(void)
{
    return (tp_timeunit)(CACurrentMediaTime() * 1000000);
}

float TP_Time_GetSecondsF(void)
{
    return (float)CACurrentMediaTime();
}

double TP_Time_GetSecondsD(void)
{
    return CACurrentMediaTime();
}