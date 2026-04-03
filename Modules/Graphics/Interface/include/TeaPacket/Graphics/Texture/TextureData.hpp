#pragma once

#include "TeaPacket/Math/Color.hpp"
#include "TeaPacket/Graphics/Texture/TextureFormat.hpp"

namespace TeaPacket::Graphics
{

    /// Represents read texture data, taken off of the GPU.
    class TextureData
    {
    public:
        /// The vector containing the raw data of the texture.
        std::vector<unsigned char> data;
        /// @brief The pitch of the texture data.
        /// @details This is the amount of bytes in a single row. Use this when reading lines instead of height.
        uint16_t pitch = 0;

        /// The width of the texture data.
        uint16_t width = 0;
        /// The height of the texture data.
        uint16_t height = 0;

        /// @brief The format this texture uses.
        /// @note This may be different from the format of the texture this was received from!
        /// The implementation is allowed to modify the texture format on creation for optimization purposes.
        TextureFormat format;

        /// Crates the TextureData and reserves the size necessary.
        explicit TextureData(const size_t dataSize = 0) :
            format()
        {
            data.reserve(dataSize);
        }

        /// @brief Gets a pixel from the texture, in RGBA8 Color4 format.
        /// @details This may fail if the texture format is not a typical RGBA8 format.
        [[nodiscard]] Color GetColor4(const uint16_t x, const uint16_t y) const
        {
            const unsigned char* p = &data[y * pitch + static_cast<unsigned int>(x * GetTextureFormatBytesPerPixel(format))];
            switch (format)
            {
                using enum TextureFormat;
            case RGBA8:
                return Color{*p, p[1], p[2], p[3]};
            case BGRA8:
                return Color{p[2], p[1], *p, p[3]};
            default: throw std::exception();
            }
        }

    };
}