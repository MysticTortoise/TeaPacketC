/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/ShaderBuffer.h"

#include <cstring>

#include <gx2/mem.h>
#include <gx2/shaders.h>

#include "GraphicsHeap/MEM2Resource.hpp"
#include "TeaPacket/Endianness/Swapping.h"
#include "TeaPacket/Graphics/GS/PlatformUniformBuffer.hpp"

using namespace TeaPacket::Graphics::GX2;

static void MemSwapShaderVar(void* data, const TP_GfxGS_VariableType varType){
    auto* spoof = static_cast<tp_u32*>(data);
    for (tp_u8 i = 0; i < varType.amount; i++)
    {
        switch (varType.baseType)
        {
        case TP_GfxGS_VariableBaseType_Float:
        case TP_GfxGS_VariableBaseType_Int:
        case TP_GfxGS_VariableBaseType_UInt:
            *spoof = TP_SwapU32(*spoof);
            spoof += 1;
            break;
        case TP_GfxGS_VariableBaseType_None:
        default:
            return;
        }
    }
}



TP_GfxGS_ShaderBuffer* TP_GfxGS_ShaderBuffer_Create(const TP_GfxGS_ShaderBufferParams* params)
{
    size_t bufSize = 0;
    for (size_t i = 0; i < params->infoList.size; i++)
    {
        bufSize += TP_GfxGS_ShaderVar_GetSize(params->infoList.p[i]);
    }
    auto* buffer = new TP_GfxGS_ShaderBuffer{
        .data = MEM2Resource<void>(0x100, bufSize),
        .size = bufSize,
    };

    if (params->data != nullptr)
    {
        memcpy(buffer->data.get(), params->data, bufSize);
        auto* data = static_cast<tp_byte*>(buffer->data.get());
        for (size_t i = 0; i < params->infoList.size; i++)
        {
            MemSwapShaderVar(data, params->infoList.p[i]);
            data += TP_GfxGS_ShaderVar_GetSize(params->infoList.p[i]);
        }
    } else
    {
        memset(buffer->data.get(), 0, bufSize);
    }

    return buffer;
}

void TP_GfxGS_ShaderBuffer_Destroy(TP_GfxGS_ShaderBuffer* buffer)
{
    delete buffer;
}

size_t TP_GfxGS_ShaderBuffer_GetSize(TP_GfxGS_ShaderBuffer* buffer)
{
    return buffer->size;
}

void TP_GfxGS_ShaderBuffer_SendRawData(TP_GfxGS_ShaderBuffer* buffer, const void* data, const size_t length,
                                       const size_t offset)
{
    void* const dest = static_cast<tp_byte*>(buffer->data.get()) + offset;
    memcpy(dest, data, length);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, dest, length);
}

void TP_GfxGS_ShaderBuffer_SetActive(TP_GfxGS_ShaderBuffer* buffer, const tp_u8 slot)
{
    GX2SetVertexUniformBlock(slot, buffer->size, buffer->data.get());
    GX2SetPixelUniformBlock(slot, buffer->size, buffer->data.get());
}

void TP_GfxGS_ShaderBuffer_SendData(TP_GfxGS_ShaderBuffer* const buffer, const void* data, const size_t offset,
    const TP_GfxGS_VariableType dataType)
{
    const size_t size = TP_GfxGS_ShaderVar_GetSize(dataType);
    void* const dest = static_cast<tp_byte*>(buffer->data.get()) + offset;
    memcpy(dest, data, size);
    MemSwapShaderVar(dest, dataType);

    GX2Invalidate(GX2_INVALIDATE_MODE_CPU | GX2_INVALIDATE_MODE_UNIFORM_BLOCK, dest, size);
}
