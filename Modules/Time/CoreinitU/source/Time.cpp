#include "TeaPacket/Time/Time.hpp"

#include <coreinit/time.h>


using namespace TeaPacket;

void Time::Initialize()
{

}

void Time::DeInitialize()
{

}

uint32_t Time::GetCurrentSeconds()
{
    return OSTicksToSeconds(OSGetTime());
}

uint64_t Time::GetCurrentMilliseconds()
{
    return OSTicksToMilliseconds(OSGetTime());
}

uint64_t Time::GetCurrentMicroseconds()
{
    return OSTicksToMicroseconds(OSGetTime());
}

float Time::GetCurrentSecondsFloat()
{
    return static_cast<float>(OSTicksToMicroseconds(OSGetTime())) * 1e-6f;
}

double Time::GetCurrentSecondsDouble()
{
    return static_cast<double>(OSTicksToNanoseconds(OSGetTime())) * 1e-9;
}
