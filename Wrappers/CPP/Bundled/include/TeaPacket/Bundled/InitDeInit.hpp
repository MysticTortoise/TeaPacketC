#pragma once

#include "TeaPacket/Bundled/Init.h"
#include "TeaPacket/Bundled/DeInit.h"

namespace TeaPacket::Bundled
{
    inline bool Init()
    {
        return TP_Bundled_Init();
    }

    inline void DeInit()
    {
        TP_Bundled_DeInit();
    }
}