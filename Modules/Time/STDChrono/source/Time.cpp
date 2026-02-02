#include "TeaPacket/Time/Time.hpp"

#include <chrono>

using namespace TeaPacket;
using namespace std;
using namespace std::chrono;

void Time::Initialize()
{

}

void Time::DeInitialize()
{

}

uint32_t Time::GetCurrentSeconds()
{
    return static_cast<uint32_t>(duration_cast<seconds>(steady_clock::now().time_since_epoch()).count());
}

uint64_t Time::GetCurrentMilliseconds()
{
    return static_cast<uint64_t>(duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count());
}

uint64_t Time::GetCurrentMicroseconds()
{
    return static_cast<uint64_t>(duration_cast<microseconds>(steady_clock::now().time_since_epoch()).count());
}

float Time::GetCurrentSecondsFloat()
{
    const duration<float> dur = steady_clock::now().time_since_epoch();
    return dur.count();
}

double Time::GetCurrentSecondsDouble()
{
    const duration<double> dur = steady_clock::now().time_since_epoch();
    return dur.count();
}
