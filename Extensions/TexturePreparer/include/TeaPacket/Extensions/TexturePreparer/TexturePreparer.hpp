#pragma once

#include "TeaPacket/Graphics/Texture/TextureFormat.hpp"


namespace TeaPacket::Extensions::TexturePreparer {
    template<Graphics::TextureFormat sourceFormat, Graphics::TextureFormat destinationFormat>
    void ConvertTextureToFormat(std::vector<unsigned char>& data) = delete;

#define DefineExternFunc(formatA, formatB) \
    template<> void ConvertTextureToFormat<Graphics::TextureFormat::formatA, Graphics::TextureFormat::formatB>(std::vector<unsigned char>&);

    DefineExternFunc(R1, R8)

#undef DefineExternFunc
}
