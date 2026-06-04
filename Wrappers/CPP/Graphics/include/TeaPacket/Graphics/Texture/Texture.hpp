#pragma once
#include "TeaPacket/Graphics/Texture/Texture.h"

#include "TeaPacket/Graphics/Texture/TextureParams.hpp"
#include "TeaPacket/Types/ClassDef.hpp"

namespace TeaPacket::Graphics
{
    class Texture
    {
        typedef TextureAvailableMode AvailableMode;
        typedef TextureFilterMode FilterMode;
        typedef TextureFormat Format;
        typedef TextureWrapMode WrapMode;

        TP_ClassWrapperDef(Texture, TP_Graphics)

        explicit Texture(TextureParams& params):
        Texture(TP_Graphics_TextureParams{
            .imageData = {
                .data = params.imageData.data,
                .pitch = params.imageData.pitch,
                .width = params.imageData.width,
                .height = params.imageData.height,
                .format = static_cast<TP_Graphics_Texture_Format>(params.imageData.format)
            },
            .filterMode = static_cast<TP_Graphics_Texture_FilterMode>(params.filterMode),
            .wrapMode = static_cast<TP_Graphics_Texture_WrapMode>(params.wrapMode)
        })
        {}

        [[nodiscard]] tp_u16 GetWidth() const
        {
            return TP_Graphics_Texture_GetWidth(p);
        }

        [[nodiscard]] tp_u16 GetHeight() const
        {
            return TP_Graphics_Texture_GetHeight(p);
        }

        [[nodiscard]] Format GetFormat() const
        {
            return static_cast<Format>(TP_Graphics_Texture_GetFormat(p));
        }

        void SetActive(const tp_u8 slot) const
        {
            TP_Graphics_Texture_SetActive(p, slot);
        }

        static bool IsFormatSupported(const Format format)
        {
            return TP_Graphics_Texture_IsFormatSupported(static_cast<TP_Graphics_Texture_Format>(format));
        }
    };
}
