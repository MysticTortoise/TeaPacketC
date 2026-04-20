#include "TeaPacket/Extensions/STBImageLoader/ImageLoader.hpp"

#include "TeaPacket/Graphics/Texture/TextureParameters.hpp"
#include "TeaPacket/Graphics/Texture/TextureFormat.hpp"
#include "TeaPacket/Assets/ReadAsset.hpp"

#include "stb_image.h"

using namespace TeaPacket;
using namespace TeaPacket::Extensions;

Graphics::Texture STBImageLoader::LoadImage(const std::string& assetPath, const Graphics::TextureParameters& wantParams)
{
    const std::vector<unsigned char> imgData = Assets::ReadBinaryFile(assetPath);
    int width, height, numComponents;
    unsigned char* data = stbi_load_from_memory(
        imgData.data(),
        static_cast<int>(imgData.size()),
        &width,
        &height,
        &numComponents,
        static_cast<int>(GetTextureFormatChannelSizes(wantParams.format).size()));

    auto trueParams = wantParams;
    trueParams.data = data;
    trueParams.width = static_cast<uint16_t>(width);
    trueParams.height = static_cast<uint16_t>(height);
    auto tex = Graphics::Texture(trueParams);

    stbi_image_free(data);
    return tex;
}
