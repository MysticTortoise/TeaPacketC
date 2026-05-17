#pragma once

#include "TeaPacket/Time/Time.h"

namespace TeaPacket::Time
{
    inline bool Init()
    {
        return TP_Time_Init();
    }

    inline void DeInit()
    {
        return TP_Time_DeInit();
    }

    inline tp_timeunit GetSeconds()
    {
        return TP_Time_GetSeconds();
    }

    inline tp_timeunit GetMilliseconds()
    {
        return TP_Time_GetMilliseconds();
    }

    inline tp_timeunit GetMicroseconds()
    {
        return TP_Time_GetMicroseconds();
    }

    inline float GetSecondsF()
    {
        return TP_Time_GetSecondsF();
    }

    inline double GetSecondsD()
    {
        return TP_Time_GetSecondsD();
    }
}