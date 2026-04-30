#include "TeaPacket/Random/Random.h"

#include <random>


static std::random_device device;
static std::mt19937 gen(device());
static std::uniform_real_distribution<float> floatDist(0, 1);

float TP_Random_F()
{
    return floatDist(gen);
}

int TP_Random_IRangeInclusive(const int min, const int max) {
    std::uniform_int_distribution<> distribution(min ,max);
    return distribution(gen);
}

unsigned int TP_Random_UIRangeInclusive(const unsigned int min, const unsigned int max) {
    std::uniform_int_distribution<unsigned int> distribution(min ,max);
    return distribution(gen);
}
