#include "TeaPacket/Graphics/Texture/Texture.hpp"
#include "TeaPacket/Graphics/PlatformTexture.hpp"

#include <gx2/texture.h>
#include <gx2/mem.h>
#include <gx2/utils.h>

#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "GraphicsHeap/MEM2Resource.hpp"
#include "TeaPacket/Graphics/Texture/TextureParameters.hpp"
#include "TeaPacket/Graphics/GX2/GX2TextureFormat.gen"
#include "TeaPacket/Graphics/GX2/GX2TextureWrap.gen"
#include "TeaPacket/Graphics/GX2/GX2TextureFilter.gen"
#include "TeaPacket/Graphics/Shader/Shader.hpp"

using namespace TeaPacket;
using namespace TeaPacket::Graphics;

Texture::Texture(const TextureParameters& parameters):
platformTexture(std::make_unique<PlatformTexture>(PlatformTexture{
    .gx2Texture = GX2Texture{
        .surface = GX2Surface{
            .dim = GX2_SURFACE_DIM_TEXTURE_2D,
            .width = parameters.width,
            .height = parameters.height,
            .depth = 1,
            .mipLevels = 1,
            .format = TextureFormatToGX2(parameters.format),
            .aa = GX2_AA_MODE1X,
            .use = GX2_SURFACE_USE_TEXTURE,
            .imageSize = 0,
            .image = nullptr,
            .mipmapSize = 0,
            .mipmaps = nullptr,
            .tileMode = GX2_TILE_MODE_DEFAULT,
            .swizzle = 0,
            .alignment = 0,
            .pitch = 0,
            .mipLevelOffset = {}
        },
        .viewFirstMip = 0,
        .viewNumMips = 1,
        .viewFirstSlice = 0,
        .viewNumSlices = 1,
        .compMap = GX2_COMP_MAP(GX2_SQ_SEL_R, GX2_SQ_SEL_G, GX2_SQ_SEL_B, GX2_SQ_SEL_A),
        .regs = {}
    },
    .gx2Sampler = GX2Sampler{},

    .isPartOfViewport = parameters.useFlags.renderTargetColor || parameters.useFlags.renderTargetDepth
})),
width(parameters.width),
height(parameters.height),
format(parameters.format)
{
    if (platformTexture->isPartOfViewport)
    {
        return; // This texture is purely dummy
    }
    GX2CalcSurfaceSizeAndAlignment(&platformTexture->gx2Texture.surface);
    GX2InitTextureRegs(&platformTexture->gx2Texture);

    if (parameters.useFlags.shaderResource)
    {
        GX2InitSampler(
            &platformTexture->gx2Sampler,
            TextureWrapModeToGX2(parameters.wrapMode),
            TextureFilterModeToGX2(parameters.filterMode));
    }

    platformTexture->gx2Texture.surface.image = MEMAllocFromDefaultHeapEx(
            platformTexture->gx2Texture.surface.imageSize,
            static_cast<int>(platformTexture->gx2Texture.surface.alignment));

    if (parameters.data != nullptr)
    {
        GX2Surface proxySurface = platformTexture->gx2Texture.surface;
        proxySurface.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
        proxySurface.pitch = proxySurface.width;
        proxySurface.image = parameters.data;
        proxySurface.imageSize = GetTextureFormatBytesPerPixel(format) * width * height;
        GX2CopySurface(&proxySurface, 0, 0, &platformTexture->gx2Texture.surface, 0, 0);
    } else
    {
        memset(platformTexture->gx2Texture.surface.image, 0, static_cast<int>(platformTexture->gx2Texture.surface.alignment));
    }
}

void Texture::SetActive(const uint8_t index)
{
    GX2SetPixelTexture(&platformTexture->gx2Texture, index);
    GX2SetPixelSampler(&platformTexture->gx2Sampler, index);
}


Texture::~Texture() = default;
Texture::Texture(Texture&& source) noexcept = default;


constexpr bool Graphics::IsTextureFormatSupported(const TextureFormat format) {
    return TextureFormatConvertableToGX2(format);
}