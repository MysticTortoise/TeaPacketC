#include "TeaPacket/Graphics/Texture/Texture.h"
#include "TeaPacket/Graphics/PlatformTexture.hpp"

#include <gx2/texture.h>
#include <gx2/mem.h>
#include <gx2/utils.h>

#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "GraphicsHeap/MEM2Resource.hpp"
#include <stdexcept>
#include "TeaPacket/Graphics/GX2/GX2TextureFormat.gen"
#include "TeaPacket/Graphics/GX2/GX2TextureWrap.gen"
#include "TeaPacket/Graphics/GX2/GX2TextureFilter.gen"

#include "TeaPacket/Graphics/Util/TextureFormatBits.h"

TP_Graphics_Texture* TP_Graphics_Texture_Create(TP_Graphics_TextureParams* params)
{
    auto* texture = new TP_Graphics_Texture{
        .gx2Texture = GX2Texture{
            .surface = GX2Surface{
                .dim = GX2_SURFACE_DIM_TEXTURE_2D,
                .width = params->width,
                .height = params->height,
                .depth = 1,
                .mipLevels = 1,
                .format = TP_Graphics_Texture_FormatToGX2(params->format),
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
    };
    GX2CalcSurfaceSizeAndAlignment(&texture->gx2Texture.surface);
    GX2InitTextureRegs(&texture->gx2Texture);

    if (params->flags.shaderResource)
    {
        GX2InitSampler(
            &texture->gx2Sampler,
            TP_Graphics_Texture_WrapModeToGX2(params->wrapMode),
            TP_Graphics_Texture_FilterModeToGX2(params->filterMode));
    }

    texture->gx2Texture.surface.image = MEMAllocFromDefaultHeapEx(
            texture->gx2Texture.surface.imageSize,
            static_cast<int>(texture->gx2Texture.surface.alignment));

    if (params->data != nullptr)
    {
        GX2Surface proxySurface = texture->gx2Texture.surface;
        proxySurface.tileMode = GX2_TILE_MODE_LINEAR_SPECIAL;
        proxySurface.pitch = proxySurface.width;
        proxySurface.image = params->data;
        proxySurface.imageSize = static_cast<uint32_t>(TP_Graphics_Helper_GetTexFormatBytesPerPixel(params->format) *
            static_cast<float>(params->width) *
            static_cast<float>(params->height));
        GX2CopySurface(&proxySurface, 0, 0, &texture->gx2Texture.surface, 0, 0);
    } else
    {
        memset(texture->gx2Texture.surface.image, 0, static_cast<int>(texture->gx2Texture.surface.alignment));
    }

    return texture;
}

void TP_Graphics_Texture_SetActive(TP_Graphics_Texture* texture, tp_u8 slot)
{
    GX2SetPixelTexture(&texture->gx2Texture, slot);
    GX2SetPixelSampler(&texture->gx2Sampler, slot);
}

tp_u16 TP_Graphics_Texture_GetWidth(TP_Graphics_Texture* const texture)
{
    return texture->gx2Texture.surface.width;
}

tp_u16 TP_Graphics_Texture_GetHeight(TP_Graphics_Texture* const texture)
{
    return texture->gx2Texture.surface.height;
}

TP_Graphics_Texture_Format TP_Graphics_Texture_GetFormat(TP_Graphics_Texture* texture)
{
    return GX2ToTP_Graphics_Texture_Format(texture->gx2Texture.surface.format);
}

void TP_Graphics_Texture_Destroy(TP_Graphics_Texture* texture)
{
    delete texture;
}

tp_bool TP_Graphics_Texture_IsFormatSupported(const TP_Graphics_Texture_Format format)
{
    return TP_Graphics_Texture_FormatConvertableToGX2(format);
}