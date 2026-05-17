#pragma once

#include "TeaPacket/Types/Array.h"

#include <string_view>

namespace TeaPacket::Types
{
    inline TP_StringView StringViewToTP(std::string_view view)
    {
        return {view.data(), view.size()};
    }
}