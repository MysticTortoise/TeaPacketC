#include "TeaPacket/Graphics/Texture/Texture.h"

#include <d3d11.h>
#include <cassert>

#include "TeaPacket/Graphics/Util/TextureFormatBits.h"
#include "TeaPacket/Graphics/PlatformTexture.hpp"
#include "TeaPacket/Graphics/WindowsGraphics.hpp"
#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"
#include "TeaPacket/Graphics/D3D11/D3D11TextureFilter.gen"
#include "TeaPacket/Graphics/D3D11/D3D11TextureWrap.gen"
#include "TeaPacket/Graphics/D3D11/D3D11TextureFormat.gen"
#include "TeaPacket/MacroUtils/StructUtils.hpp"

using namespace TeaPacket::Graphics::D3D11;

static constexpr D3D11_USAGE GetD3DUsage(const TP_Graphics_TextureUseFlags flags)
{
    switch (flags.writeMode)
    {
    case TP_Graphics_Texture_AvailableMode_None:
        return D3D11_USAGE_IMMUTABLE;
    case TP_Graphics_Texture_AvailableMode_CPU:
        return D3D11_USAGE_DYNAMIC;
    case TP_Graphics_Texture_AvailableMode_GPU:
        return D3D11_USAGE_DEFAULT;
    default:
        assert(false);
        return D3D11_USAGE_DEFAULT;
    }
}

static constexpr D3D11_BIND_FLAG GetD3DBindFlags(const TP_Graphics_TextureUseFlags flags)
{
    UINT flag = 0;
    if (flags.shaderResource) { flag |= D3D11_BIND_SHADER_RESOURCE; }
    //if (flags.renderTargetColor) { flag |= D3D11_BIND_RENDER_TARGET; }
    //if (flags.renderTargetDepth) { flag |= D3D11_BIND_DEPTH_STENCIL; }
    return static_cast<D3D11_BIND_FLAG>(flag);
}

static constexpr D3D11_CPU_ACCESS_FLAG GetD3DCpuAccessFlags(const TP_Graphics_TextureUseFlags flags)
{
    return static_cast<D3D11_CPU_ACCESS_FLAG>(
        flags.writeMode == TP_Graphics_Texture_AvailableMode_CPU ? D3D11_CPU_ACCESS_WRITE : 0
        );
}

TP_Graphics_Texture* TP_Graphics_Texture_Create(TP_Graphics_TextureParams* params)
{
    auto* tex = new TP_Graphics_Texture;

    auto texture = new TP_Graphics_Texture();
    texture->width = params->width;
    texture->height = params->height;
    texture->format = params->format;

    D3D11_TEXTURE2D_DESC textureDesc;
    textureDesc.Width = texture->width;
    textureDesc.Height = texture->height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = TP_Graphics_Texture_FormatToD3D(texture->format);
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = GetD3DUsage(params->flags);
    textureDesc.BindFlags = GetD3DBindFlags(params->flags);
    textureDesc.CPUAccessFlags = GetD3DCpuAccessFlags(params->flags);
    textureDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA texData = {
        .pSysMem = params->data,
        .SysMemPitch = static_cast<UINT>(static_cast<float>(params->width) * TP_Graphics_Helper_GetTexFormatBytesPerPixel(params->format)),
        .SysMemSlicePitch = 0
    };

    CheckErrorWinCom(
        device->CreateTexture2D(&textureDesc,
            params->data == nullptr ? nullptr : &texData, tex->texture2D.GetAddressOf())
    );

    if (params->data == nullptr)
    {
        assert(params->flags.writeMode != TP_Graphics_Texture_AvailableMode_None);
    }

    if (params->flags.shaderResource)
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = UINT_MAX;
        CheckErrorWinCom(
            device->CreateShaderResourceView(
                tex->texture2D.Get(), &srvDesc, tex->shaderResourceView.GetAddressOf()
                )
        );
        deviceContext->GenerateMips(tex->shaderResourceView.Get());

        D3D11_SAMPLER_DESC samplerDesc;
        samplerDesc.Filter = TP_Graphics_Texture_FilterModeToD3D(params->filterMode);
        D3D11_TEXTURE_ADDRESS_MODE d3dWrapType = TP_Graphics_Texture_WrapModeToD3D(params->wrapMode);
        samplerDesc.AddressU = d3dWrapType;
        samplerDesc.AddressV = d3dWrapType;
        samplerDesc.AddressW = d3dWrapType;
        samplerDesc.MipLODBias = 0;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        ZeroStruct(samplerDesc.BorderColor);
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        CheckErrorWinCom(
            device->CreateSamplerState(&samplerDesc, tex->samplerState.GetAddressOf())
        );
    }

    return tex;
}
/*
TextureData Texture::GetData() const
{
    D3D11_TEXTURE2D_DESC stagingDesc;
    platformTexture->texture2D->GetDesc(&stagingDesc);
    stagingDesc.Usage = D3D11_USAGE_STAGING;
    stagingDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    stagingDesc.BindFlags = 0;
    stagingDesc.MiscFlags = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTex;
    CheckErrorWinCom(
        device->CreateTexture2D(&stagingDesc, NULL,
            stagingTex.GetAddressOf())
    );

    deviceContext->CopyResource(
        stagingTex.Get(),
        platformTexture->texture2D.Get());

    D3D11_MAPPED_SUBRESOURCE mappedResource;
    CheckErrorWinCom(
    deviceContext->Map(stagingTex.Get(),
        0, D3D11_MAP_READ, 0, &mappedResource)
    );

    const uint8_t bpp = GetTextureFormatBPP(platformTexture->format);
    const uint_fast16_t h = platformTexture->height;

    TextureData data = TextureData(bpp * mappedResource.RowPitch * h);
    data.width = static_cast<uint16_t>(stagingDesc.Width);
    data.height = static_cast<uint16_t>(stagingDesc.Height);
    data.format = D3DToTextureFormat(stagingDesc.Format);
    data.pitch = static_cast<uint16_t>(mappedResource.RowPitch);

    unsigned char* srcBeg;
    for (uint_fast16_t y = 0; y < h; y++)
    {
        srcBeg = static_cast<unsigned char*>(mappedResource.pData) + mappedResource.RowPitch * y;
        data.data.insert(data.data.end(), srcBeg, srcBeg + mappedResource.RowPitch);
    }
    deviceContext->Unmap(stagingTex.Get(),0);
    return data;
}*/

void TP_Graphics_Texture_SetActive(TP_Graphics_Texture* texture, tp_u8 slot)
{
    deviceContext->PSSetShaderResources(slot, 1, texture->shaderResourceView.GetAddressOf());
    deviceContext->PSSetSamplers(slot, 1, texture->samplerState.GetAddressOf());
}

tp_u16 TP_Graphics_Texture_GetWidth(TP_Graphics_Texture* texture)
{
    return texture->width;
}

tp_u16 TP_Graphics_Texture_GetHeight(TP_Graphics_Texture* texture)
{
    return texture->height;
}

TP_Graphics_Texture_Format TP_Graphics_Texture_GetFormat(TP_Graphics_Texture* texture)
{
    return texture->format;
}

tp_bool TP_Graphics_Texture_IsFormatSupported(const TP_Graphics_Texture_Format format)
{
    // ReSharper disable once CppDFAConstantConditions
    if (!TP_Graphics_Texture_FormatConvertableToD3D(format))
        return tp_false;

    UINT formatSupport;
    const HRESULT result = device->CheckFormatSupport(TP_Graphics_Texture_FormatToD3D(format), &formatSupport);
    if (result == E_INVALIDARG)
    {
        // shit
        return tp_false;
    }
    return !!(formatSupport & (D3D11_FORMAT_SUPPORT_TEXTURE2D));
}

void TP_Graphics_Texture_Destroy(TP_Graphics_Texture* texture)
{
    delete texture;
}

/*
TextureFormat Graphics::ConvertTextureToSupportedFormat(std::vector<unsigned char>& data, const TextureFormat sourceFormat)
{

    switch (sourceFormat)
    {
    case TextureFormat::R1:
        if (IsTextureFormatSupported(TextureFormat::R8))
        {
            Extensions::TexturePreparer::ConvertTextureToFormat<TextureFormat::R1, TextureFormat::R8>(data);
            return TextureFormat::R8;
        } else
        {
            throw std::exception("Format R8 not supported - add more pls");
        }
    default:
        return sourceFormat;
    }
}
*/
