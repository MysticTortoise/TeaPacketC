#pragma once
#include "TeaPacket/Core/Core.hpp"
#include <cstdint>

namespace TeaPacket::Time
{
    void Initialize();
    void DeInitialize();

    // Gets the current time in seconds since an implementation-defined time.
    uint32_t GetCurrentSeconds();
    uint64_t GetCurrentMilliseconds();
    uint64_t GetCurrentMicroseconds();

    float GetCurrentSecondsFloat();
    double GetCurrentSecondsDouble();

}
TP_HookInitDeInitFunctions(Time, 1);