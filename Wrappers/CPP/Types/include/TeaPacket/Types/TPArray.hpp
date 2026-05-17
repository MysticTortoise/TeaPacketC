#pragma once

#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Types/Array.h"

#include <cstring>

namespace TeaPacket
{
    template<typename T>
    class TPArray
    {
    public:
        TP_Array(T) arr;

        TPArray(T* p, const size_t size):arr{p, size} {}

        ~TPArray()
        {
            TP_MemFree(arr.p);
        }
    };

#define SpanToTPArray(span) { span.data(), span.size() }
#define SpanToTPArrayCast(span, newType) { reinterpret_cast<newType*>(span.data()), span.size() }
}