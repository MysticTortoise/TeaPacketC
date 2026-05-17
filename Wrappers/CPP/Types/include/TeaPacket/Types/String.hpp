#pragma once

#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Types/Array.h"

#include <cstring>

namespace TeaPacket
{
    class TPString
    {

    public:
        TP_String str;

        explicit TPString(TP_String& moveFrom):
        str(moveFrom)
        {
            moveFrom.p = nullptr;
            moveFrom.size = 0;
        }

        explicit TPString(const TP_String moveFrom):str(moveFrom){}

        explicit TPString(const char* charList, const size_t size):str{
            static_cast<char*>(TP_MemAlloc(size)),
            size
        }
        {
            memcpy(str.p, charList, size);
        }

        ~TPString()
        {
            TP_MemFree(str.p);
        }
    };
}