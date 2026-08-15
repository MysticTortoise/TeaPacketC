#pragma once
#include <string>

#include "TeaPacket/Types/Array.h"

namespace TeaPacket::Assets::CPPSTDFile
{
    inline std::string GetFilePath(const TP_StringView assetPath)
    {
        std::string assetSource(TP_ASSETS_ASSETPREPEND);
        assetSource.append(assetPath.p, assetPath.size);
        return assetSource;
    }
}
