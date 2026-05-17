#pragma once

#include "TeaPacket/Random/Random.h"

namespace TeaPacket::Random
{
    inline float RandFloat()
    {
        return TP_Random_F();
    }

    inline int RandIntRangeInclusive(const int min, const int max)
    {
        return TP_Random_IRangeInclusive(min, max);
    }

    inline unsigned int RandUIntRangeInclusive(const unsigned int min, const unsigned int max)
    {
        return TP_Random_UIRangeInclusive(min, max);
    }
}