#include "TeaPacket/Extensions/TexturePreparer/TexturePreparer.hpp"

using namespace TeaPacket::Extensions;


template<>
void TexturePreparer::ConvertTextureToFormat<TeaPacket::Graphics::TextureFormat::R1, TeaPacket::Graphics::TextureFormat
::R8>(std::vector<unsigned char>& data) {
    std::vector<unsigned char> newData(data.size() * 8);
    size_t i = 0;
    for (const unsigned char byte : data)
    {
        for (signed int j = 0; j < 8; ++j)
        {
            newData[i] = ((byte >> (7-j)) & 1) ? 255 : 0;
            ++i;
        }
    }
    data = std::move(newData);
}

