#pragma once
#include <memory>

#include "TeaPacket/MacroUtils/ClassDefUtils.hpp"

namespace TeaPacket::Graphics
{
    struct PlatformTexture;
    struct TextureParameters;
    class TextureData;
    enum class TextureFormat : unsigned short;

    /// Represents a texture on the GPU.
    class Texture
    {
    public:
        /// Gets the width of the texture.
        [[nodiscard]] uint16_t GetWidth() const;
        /// Gets the height of the texture.
        [[nodiscard]] uint16_t GetHeight() const;
        // Gets the texture's format.
        [[nodiscard]] TextureFormat GetFormat() const;

        /// A pointer to the implementation-defined data this texture uses.
        std::unique_ptr<PlatformTexture> platformTexture;

        /// Creates a texture using parameters.
        explicit Texture(const TextureParameters& parameters);
        ~Texture();

        TP_OBJ_MOVE_NO_COPY(Texture)

        /// Get the pixel data of this texture. Only works if cpuReadable is set when this texture is created.
        [[nodiscard]] TextureData GetData() const;
        /// Binds this texture to the specified texture slot, to be used whenever DrawMesh() is called.
        void SetActive(uint8_t index);
    };
}
