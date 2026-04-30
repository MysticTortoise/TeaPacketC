#include "TeaPacket/Graphics/ShaderBuffer.h"

#include <cassert>
#include <d3d11.h>

#include <memory>

#include "TeaPacket/Graphics/ShaderBufferParams.h"
#include "TeaPacket/Graphics/PlatformUniformBuffer.hpp"
#include "TeaPacket/Graphics/WindowsGraphics.hpp"
#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"

using namespace TeaPacket::Graphics::D3D11;

TP_Graphics_ShaderBuffer* TP_Graphics_ShaderBuffer_Create(TP_Graphics_ShaderBufferParams* params)
{

    const auto bufferDesc = D3D11_BUFFER_DESC{
        .ByteWidth = static_cast<UINT>(params->size),
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


    auto* buffer = new TP_Graphics_ShaderBuffer;
    CheckErrorWinCom(
        device->CreateBuffer(
            &bufferDesc,
            params->data == nullptr ? nullptr : &subResourceData,
            buffer->cbuffer.GetAddressOf())
    );
    buffer->size = params->size;


    return buffer;
}

void TP_Graphics_ShaderBuffer_SendData(TP_Graphics_ShaderBuffer* const buffer, const void* data, const size_t length, size_t offset)
{
    ID3D11Buffer* bufferPtr = buffer->cbuffer.Get();
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    CheckErrorWinCom( deviceContext->Map(
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

void TP_Graphics_ShaderBuffer_SetActive(TP_Graphics_ShaderBuffer* buffer, tp_u8 slot)
{
    deviceContext->VSSetConstantBuffers(slot, 1, buffer->cbuffer.GetAddressOf());
    deviceContext->PSSetConstantBuffers(slot, 1, buffer->cbuffer.GetAddressOf());
}

const tp_bool TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped = tp_true;

void TP_Graphics_ShaderBuffer_Destroy(TP_Graphics_ShaderBuffer* const buffer)
{
    delete[] buffer;
}

size_t TP_Graphics_ShaderBuffer_GetSize(TP_Graphics_ShaderBuffer* const buffer)
{
    return buffer->size;
}

