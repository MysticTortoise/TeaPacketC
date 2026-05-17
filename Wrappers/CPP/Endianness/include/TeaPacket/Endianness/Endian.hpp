#pragma once
#include <cstdint>

#include "TeaPacket/Endianness/Endian.h"

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace TeaPacket::Assets
{
    template<typename T> T Swap(T val) = delete;

    template<> inline uint8_t Swap(const uint8_t val) { return val; }
    template<> inline  int8_t Swap(const  int8_t val) { return val; }
    template<> inline  char   Swap(const char    val) { return val; }
    template<> inline  bool   Swap(const bool    val) { return val; }

    template<>
    inline uint16_t Swap(const uint16_t val)
    {
        return TP_SwapU16(val);
    }

    template<>
    inline int16_t Swap(const int16_t val)
    {
        return TP_SwapI16(val);
    }

    template<>
    inline uint32_t Swap(const uint32_t val)
    {
        return TP_SwapU32(val);
    }

        template<>
    inline int32_t Swap(const int32_t val)
    {
        return TP_SwapI32(val);
    }

    template<>
    inline uint64_t Swap(const uint64_t val)
    {
        return TP_SwapU64(val);
    }

    template<>
    inline int64_t Swap(const int64_t val)
    {
        return TP_SwapI64(val);
    }

    template<>
    inline float Swap(float val)
    {
#if __cplusplus >= 202002L
        return std::bit_cast<float>(Swap<uint32_t>(std::bit_cast<uint32_t>(val)));
#else
        static_assert(sizeof(float) == sizeof(uint32_t), "FLOAT NOT 32 BIT, PLEASE FIX THIS FUNCTION");
        uint32_t r;
        memcpy(&r, &val, sizeof(float));
        r = Swap(r);
        memcpy(&val, &r, sizeof(float));
        return val;
#endif
    }

        template<>
    inline double Swap(double val)
    {
#if __cplusplus >= 202002L
            return std::bit_cast<double>(Swap<uint64_t>(std::bit_cast<uint64_t>(val)));
#else
            static_assert(sizeof(double) == sizeof(uint64_t), "DOUBLE NOT 64 BIT, PLEASE FIX THIS FUNCTION");
            uint64_t r;
            memcpy(&r, &val, sizeof(double));
            r = Swap(r);
            memcpy(&val, &r, sizeof(double));
            return val;
#endif
    }

    constexpr uint32_t _uint32_ = 0x01020304;
    constexpr uint8_t _magic_ = static_cast<const uint8_t&>(_uint32_);

    /// Whether the current platform is Big Endian or not.
    constexpr bool IsBigEndian()
    {
#if __cplusplus >= 202002L
        return std::endian::native == std::endian::big;
#else
        return _magic_ == 0x01;
#endif
    }
}
