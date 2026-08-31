/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/ShaderBuffer.h"

#include <cassert>
#include <d3d11.h>

#include <memory>

#include "TeaPacket/Graphics/GS/PlatformUniformBuffer.hpp"
#include "TeaPacket/Graphics/GS/ShaderBufferParams.h"
#include "TeaPacket/Graphics/GS/VariableType.h"
#include "TeaPacket/Graphics/GS/WindowsGraphics.hpp"
#include "TeaPacket/Graphics/GS/D3D11/WinMacro.hpp"

using namespace TeaPacket::Graphics::D3D11;


TP_GfxGS_ShaderBuffer* TP_GfxGS_ShaderBuffer_Create(const TP_GfxGS_ShaderBufferParams* params)
{
    size_t bufSize = 0;
    for (size_t i = 0; i < params->infoList.size; i++)
    {
        bufSize += TP_GfxGS_ShaderVar_GetSize(params->infoList.p[i]);
    }

    const size_t internalSize = bufSize + 16 - (bufSize % 16);

    const auto bufferDesc = D3D11_BUFFER_DESC{
        .ByteWidth = static_cast<UINT>(internalSize),
        .Usage = D3D11_USAGE_DYNAMIC,
        .BindFlags = D3D11_BIND_CONSTANT_BUFFER,
        .CPUAccessFlags = D3D11_CPU_ACCESS_WRITE,
        .MiscFlags = 0,
        .StructureByteStride = 0,
    };

    const auto subResourceData = D3D11_SUBRESOURCE_DATA{
        .pSysMem = params->data,
        .SysMemPitch = 0,
        .SysMemSlicePitch = 0,
    };


    auto* buffer = new TP_GfxGS_ShaderBuffer;
    CheckErrorWinCom(
        device->CreateBuffer(
            &bufferDesc,
            params->data == nullptr ? nullptr : &subResourceData,
            buffer->cbuffer.GetAddressOf())
    );
    buffer->size = internalSize;


    return buffer;
}

void TP_GfxGS_ShaderBuffer_SendRawData(TP_GfxGS_ShaderBuffer* const buffer, const void* data, const size_t length,
                                       size_t offset)
{
    ID3D11Buffer* bufferPtr = buffer->cbuffer.Get();
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    CheckErrorWinCom(deviceContext->Map(
        bufferPtr,
        0,
        D3D11_MAP_WRITE_DISCARD,
        0,
        &mappedResource
    ));
    assert(offset + length <= buffer->size);
    memcpy(static_cast<char*>(mappedResource.pData) + offset, data, length);
    deviceContext->Unmap(bufferPtr, 0);
}

void TP_GfxGS_ShaderBuffer_SendData(TP_GfxGS_ShaderBuffer* const buffer, const void* data, const size_t offset, const TP_GfxGS_VariableType varType)
{
    TP_GfxGS_ShaderBuffer_SendRawData(buffer, data, TP_GfxGS_ShaderVar_GetSize(varType), offset);
}

void TP_GfxGS_ShaderBuffer_SetActive(TP_GfxGS_ShaderBuffer* buffer, tp_u8 slot)
{
    deviceContext->VSSetConstantBuffers(slot, 1, buffer->cbuffer.GetAddressOf());
    deviceContext->PSSetConstantBuffers(slot, 1, buffer->cbuffer.GetAddressOf());
}

void TP_GfxGS_ShaderBuffer_Destroy(TP_GfxGS_ShaderBuffer* const buffer)
{
    delete buffer;
}

size_t TP_GfxGS_ShaderBuffer_GetSize(TP_GfxGS_ShaderBuffer* const buffer)
{
    return buffer->size;
}
