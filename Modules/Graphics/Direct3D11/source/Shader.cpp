#include "TeaPacket/Graphics/Shader/Shader.h"

#include <vector>

#include <d3dcompiler.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/PlatformShader.hpp"
#include "TeaPacket/Graphics/WindowsGraphics.hpp"

#include "TeaPacket/Graphics/Shader/ShaderParams.h"
#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"

#include "TeaPacket/Logging/Logging.h"

using namespace TeaPacket::Graphics::D3D11;


static constexpr DXGI_FORMAT GetDXGIFormatFromVertexAttribute(const TP_Graphics_Shader_VariableType shaderVarType)
{
    switch (shaderVarType.amount)
    {
    case 1:
        switch (shaderVarType.baseType)
        {
    case TP_Graphics_Shader_VariableBaseType_Float:     return DXGI_FORMAT_R32_FLOAT;
    case TP_Graphics_Shader_VariableBaseType_Int:       return DXGI_FORMAT_R32_SINT;
    case TP_Graphics_Shader_VariableBaseType_UInt:      return DXGI_FORMAT_R32_UINT;
    case TP_Graphics_Shader_VariableBaseType_None:
    default:
            return DXGI_FORMAT_UNKNOWN;
        }
        break;
    case 2:
        switch (shaderVarType.baseType)
        {
    case TP_Graphics_Shader_VariableBaseType_Float: return DXGI_FORMAT_R32G32_FLOAT;
    case TP_Graphics_Shader_VariableBaseType_Int: return DXGI_FORMAT_R32G32_SINT;
    case TP_Graphics_Shader_VariableBaseType_UInt: return DXGI_FORMAT_R32G32_UINT;
    case TP_Graphics_Shader_VariableBaseType_None:
    default:
            return DXGI_FORMAT_UNKNOWN;

        }
        break;
    case 3:
        switch (shaderVarType.baseType)
        {
    case TP_Graphics_Shader_VariableBaseType_Float: return DXGI_FORMAT_R32G32B32_FLOAT;
    case TP_Graphics_Shader_VariableBaseType_Int: return DXGI_FORMAT_R32G32B32_SINT;
    case TP_Graphics_Shader_VariableBaseType_UInt: return DXGI_FORMAT_R32G32B32_UINT;
    case TP_Graphics_Shader_VariableBaseType_None:
    default:
            return DXGI_FORMAT_UNKNOWN;
        }
        break;
    case 4:
        switch (shaderVarType.baseType)
        {
    case TP_Graphics_Shader_VariableBaseType_Float: return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case TP_Graphics_Shader_VariableBaseType_Int: return DXGI_FORMAT_R32G32B32A32_SINT;
    case TP_Graphics_Shader_VariableBaseType_UInt: return DXGI_FORMAT_R32G32B32A32_UINT;
    case TP_Graphics_Shader_VariableBaseType_None:
    default:
            return DXGI_FORMAT_UNKNOWN;
        }
        break;
    default:
        return DXGI_FORMAT_UNKNOWN;
    }
}

TP_Graphics_Shader* TP_Graphics_Shader_Create(TP_Graphics_ShaderParams* const params)
{
    Microsoft::WRL::ComPtr<ID3D10Blob> errorMessage;

    Microsoft::WRL::ComPtr<ID3D10Blob> vertexShaderBuffer;
    // Compile Vertex Shader
    HRESULT result = D3DCompile(
        params->vertexShaderCode.p, params->vertexShaderCode.size,
        nullptr, nullptr, nullptr,
        "main", "vs_5_0",
        D3D10_SHADER_ENABLE_STRICTNESS, 0,
        vertexShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf()
        );
    // Check Vertex Shader Compilation for errors
    if (FAILED(result))
    {
        if (errorMessage.Get())
        {
            const char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
            const size_t size = errorMessage->GetBufferSize();
            TP_LogCharN(compileErrors, size);
            TP_LogConstStr("D3D11 Shader failed to compile, see log for errors....");
            return nullptr;
        }
        TP_LogConstStr("D3D11 Shader failed to compile, no error given!!! fuck :D");
        return nullptr;
    }



    Microsoft::WRL::ComPtr<ID3D10Blob> pixelShaderBuffer;
    // Compile Pixel Shader
    result =
        D3DCompile(
            params->fragmentShaderCode.p, params->fragmentShaderCode.size,
            nullptr, nullptr, nullptr,
            "main", "ps_5_0",
            D3D10_SHADER_ENABLE_STRICTNESS, 0,
            pixelShaderBuffer.GetAddressOf(), errorMessage.GetAddressOf()
            );
    // Check Pixel Shader for errors
    if (FAILED(result))
    {
        if (errorMessage.Get())
        {
            const char* compileErrors = static_cast<char*>(errorMessage->GetBufferPointer());
            const size_t size = errorMessage->GetBufferSize();
            TP_LogCharN(compileErrors, size);
            TP_LogConstStr("D3D11 Shader failed to compile, see log for errors....");
            return nullptr;
        }
        TP_LogConstStr("D3D11 Shader failed to compile, no error given!!! fuck :D");
        return nullptr;
    }

    auto* shader = new TP_Graphics_Shader;

    // Create both shaders
    CheckErrorWinCom(
        device->CreateVertexShader(
            vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
            nullptr, shader->vertexShader.GetAddressOf()
            ));

    CheckErrorWinCom(
        device->CreatePixelShader(
            pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(),
            nullptr, shader->pixelShader.GetAddressOf()
    ));
    // Setup input variables
    std::vector<D3D11_INPUT_ELEMENT_DESC> polygonLayout;
    polygonLayout.reserve(params->inputAttributes.size);
    for (size_t i = 0; i < params->inputAttributes.size; i++)
    {
        polygonLayout.emplace_back(D3D11_INPUT_ELEMENT_DESC{
            .SemanticName = "TEXCOORD",
            .SemanticIndex = static_cast<unsigned int>(i),
            .Format = GetDXGIFormatFromVertexAttribute(params->inputAttributes.p[i]),
            .InputSlot = 0,
            .AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT,
            .InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA,
            .InstanceDataStepRate = 0
        });
    }

    CheckErrorWinCom(
        device->CreateInputLayout(polygonLayout.data(), static_cast<UINT>(params->inputAttributes.size),
            vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
            shader->inputLayout.GetAddressOf()
            ));

    return shader;
}

void TP_Graphics_Shader_SetActive(TP_Graphics_Shader* const shader)
{
    deviceContext->IASetInputLayout(shader->inputLayout.Get());
    deviceContext->VSSetShader(shader->vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(shader->pixelShader.Get(), nullptr, 0);
}

void TP_Graphics_Shader_Destroy(TP_Graphics_Shader* shader)
{
    delete[] shader;
}
