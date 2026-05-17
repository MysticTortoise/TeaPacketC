#pragma once
#include "TeaPacket/Graphics/ShaderBuffer.h"

#include "TeaPacket/Graphics/ShaderBufferParams.hpp"
#include "TeaPacket/Types/ClassDef.hpp"

namespace TeaPacket::Graphics
{
    class ShaderBuffer
    {
        TP_ClassWrapperDef(ShaderBuffer, TP_Graphics)

        explicit ShaderBuffer(const ShaderBufferParams& params):
        ShaderBuffer(TP_Graphics_ShaderBufferParams{
            .data = params.data,
            .size = params.size
        }) {}

        size_t GetSize() const
        {
            return TP_Graphics_ShaderBuffer_GetSize(p);
        }

        void SendData(const void* data, const size_t length, const size_t offset) const
        {
            TP_Graphics_ShaderBuffer_SendData(p, data, length, offset);
        }

        void SetActive(const tp_u8 slot) const
        {
            TP_Graphics_ShaderBuffer_SetActive(p, slot);
        }

        const inline static bool ShouldBeEndianSwapped = TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped;
    };
}
