#include "TeaPacket/Time/Time.h"

#include <chrono>

using namespace std::chrono;

tp_bool TP_Time_Init(){return tp_true;}
void TP_Time_DeInit() {}

tp_timeunit TP_Time_GetSeconds()
{
    return static_cast<tp_timeunit>(duration_cast<seconds>(steady_clock::now().time_since_epoch()).count());
}

tp_timeunit TP_Time_GetMilliseconds()
{
    return static_cast<tp_timeunit>(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

tp_timeunit TP_Time_GetMicroseconds()
{
    return static_cast<tp_timeunit>(duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count());
}

float TP_Time_GetSecondsF()
{
    const duration<float> dur = steady_clock::now().time_since_epoch();
    return dur.count();
}

double TP_Time_GetSecondsD()
{
    const duration<double> dur = steady_clock::now().time_since_epoch();
    return dur.count();
}
