#include "TeaPacket/Graphics/ShaderBuffer.h"

#include <cstring>
#include <gx2/mem.h>
#include <gx2/shaders.h>

#include "GraphicsHeap/MEM2Resource.hpp"
#include "TeaPacket/Graphics/PlatformUniformBuffer.hpp"

using namespace TeaPacket::Graphics::GX2;

const tp_bool TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped = true;

TP_Graphics_ShaderBuffer* TP_Graphics_ShaderBuffer_Create(TP_Graphics_ShaderBufferParams* params)
{
    auto* buffer = new TP_Graphics_ShaderBuffer{
        .data = MEM2Resource<void>(0x100, params->size),
        .size = params->size,
    };

    if (params->data != nullptr)
    {
        memcpy(buffer->data.get(), params->data, params->size);
    } else
    {
        memset(buffer->data.get(), 0, params->size);
    }

    return buffer;
}

void TP_Graphics_ShaderBuffer_Destroy(TP_Graphics_ShaderBuffer* buffer)
{
    delete buffer;
}

size_t TP_Graphics_ShaderBuffer_GetSize(TP_Graphics_ShaderBuffer* buffer)
{
    return buffer->size;
}

void TP_Graphics_ShaderBuffer_SendData(TP_Graphics_ShaderBuffer* buffer, const void* data, const size_t length, const size_t offset)
{
    memcpy(static_cast<tp_byte*>(buffer->data.get()) + offset, data, length);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, buffer->data.get(), buffer->size);
}

void TP_Graphics_ShaderBuffer_SetActive(TP_Graphics_ShaderBuffer* buffer, const tp_u8 slot)
{
    GX2SetVertexUniformBlock(slot, buffer->size, buffer->data.get());
    GX2SetPixelUniformBlock (slot, buffer->size, buffer->data.get());
}
