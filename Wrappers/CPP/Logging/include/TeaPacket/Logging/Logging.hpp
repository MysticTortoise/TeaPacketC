#pragma once

#include "TeaPacket/Logging/Logging.h"

#include <string_view>

#include "TeaPacket/Types/StringView.hpp"

namespace TeaPacket
{
    namespace Logging
    {
        inline bool Init()
        {
            return TP_Logging_Init();
        }

        inline void DeInit()
        {
            TP_Logging_DeInit();
        }
    }

#define LogSNumDef(type) \
    inline void Log(const type msg) \
    { \
        TP_LogSLong(msg); \
    }

    LogSNumDef(signed short int);
    LogSNumDef(signed int);
    LogSNumDef(signed long int);
#undef LogSNumDef

#define LogUNumDef(type) \
    inline void Log(const type msg) \
    { \
        TP_LogULong(msg); \
    }

    LogUNumDef(unsigned short int);
    LogUNumDef(unsigned int);
    LogUNumDef(unsigned long int);
#undef LogUNumDef


    inline void Log(const float x)
    {
        TP_LogDouble(x);
    }

    inline void Log(const double x)
    {
        TP_LogDouble(x);
    }

    inline void Log(const char c)
    {
        TP_LogChar(c);
    }

    inline void Log(const unsigned char c)
    {
        TP_LogByte(c);
    }

    inline void Log(const bool b)
    {
        TP_LogBool(b);
    }

    inline void Log(const std::string_view view)
    {
        TP_LogString(Types::StringViewToTP(view));
    }

    inline void Log(const char* c, const size_t size)
    {
        TP_LogCharN(c, size);
    }


}
