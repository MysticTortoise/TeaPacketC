#pragma once

#include "TeaPacket/System/System.h"

namespace TeaPacket::System
{
    inline bool Init()
    {
        return TP_System_Init();
    }

    inline void DeInit()
    {
        TP_System_DeInit();
    }

    inline void Process()
    {
        TP_System_Process();
    }

    inline bool ShouldRun()
    {
        return TP_System_ShouldRun();
    }
}