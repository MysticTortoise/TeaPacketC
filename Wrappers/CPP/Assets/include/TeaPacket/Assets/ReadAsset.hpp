#pragma once
#include "TeaPacket/Assets/ReadAsset.h"

#include "TeaPacket/Types/String.hpp"
#include <string_view>

#include "TeaPacket/Types/StringView.hpp"
#include "TeaPacket/Types/TPArray.hpp"

namespace TeaPacket::Assets
{
    inline TPString ReadTextAsset(const std::string_view assetPath)
    {
        return TPString(TP_Assets_ReadTextAsset(Types::StringViewToTP(assetPath)));
    }

    inline TPArray<tp_byte> ReadBinaryAsset(const std::string_view assetPath)
    {
        const TP_ByteArray ba = TP_Assets_ReadBinaryAsset(Types::StringViewToTP(assetPath));
        return {ba.p, ba.size};
    }
}
