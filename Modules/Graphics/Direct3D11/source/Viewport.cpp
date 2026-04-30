#include "TeaPacket/Graphics/Viewport.h"

#include "TeaPacket/Graphics/Texture/TextureParams.h"
#include "TeaPacket/Graphics/ViewportParams.h"

#include <d3d11.h>
#include <iostream>
#include <cassert>

#include "TeaPacket/Graphics/PlatformTexture.hpp"
#include "TeaPacket/Graphics/PlatformViewport.hpp"
#include "TeaPacket/Graphics/Texture/Format.h"
#include "TeaPacket/Graphics/WindowsGraphics.hpp"
#include "TeaPacket/Graphics/Texture/Texture.h"
#include "TeaPacket/MacroUtils/StructUtils.hpp"
#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"

using namespace TeaPacket::Graphics::D3D11;

TP_Graphics_Viewport* TP_Graphics_Viewport_Create(TP_Graphics_ViewportParams* params)
{
    auto* viewport = new TP_Graphics_Viewport;

    {
        auto texParms = TP_Graphics_TextureParams{
            .data = nullptr,
            .width = params->width,
            .height = params->height,
            .format = TP_Graphics_Texture_Format_BGRA8,
            .filterMode = TP_Graphics_Texture_FilterMode_Linear,
            .wrapMode = TP_Graphics_Texture_WrapMode_Wrap,
            .flags = {
                .shaderResource = params->shaderUsable,
                .cpuReadable = true,
                .writeMode = TP_Graphics_Texture_AvailableMode_GPU,
            }
        };
        viewport->colorTex = TP_Graphics_Texture_Create(&texParms);
    }
    {
        auto texParms = TP_Graphics_TextureParams{
            .data = nullptr,
            .width = params->width,
            .height = params->height,
            .format = TP_Graphics_Texture_Format_D24S8,
            .filterMode = TP_Graphics_Texture_FilterMode_Linear,
            .wrapMode = TP_Graphics_Texture_WrapMode_Wrap,
            .flags = {
                .shaderResource = params->shaderUsable,
                .cpuReadable = true,
                .writeMode = TP_Graphics_Texture_AvailableMode_GPU,
            }
        };
        viewport->depthTex = TP_Graphics_Texture_Create(&texParms);
    }

    D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
    D3D11_TEXTURE2D_DESC texDesc;
    viewport->colorTex->texture2D->GetDesc(&texDesc);
    renderTargetViewDesc.Format = texDesc.Format;
    renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
    renderTargetViewDesc.Texture2D.MipSlice = 0;

    CheckErrorWinCom(
        device->CreateRenderTargetView(
            viewport->colorTex->texture2D.Get(), &renderTargetViewDesc,
            viewport->renderTargetView.GetAddressOf())
    );

    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroStruct(depthStencilViewDesc);
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilViewDesc.Texture2D.MipSlice = 0;

    CheckErrorWinCom(
        device->CreateDepthStencilView(viewport->depthTex->texture2D.Get(), &depthStencilViewDesc,
            viewport->depthStencilView.GetAddressOf())
    );

    viewport->d3dViewport = D3D11_VIEWPORT{
        .TopLeftX = 0,
        .TopLeftY = 0,
        .Width = static_cast<float>(params->width),
        .Height = static_cast<float>(params->height),
        .MinDepth = 0,
        .MaxDepth = 1,
    };

    return viewport;

}

static TP_Graphics_Viewport* activeViewport;

void TP_Graphics_Viewport_Destroy(const TP_Graphics_Viewport* viewport)
{
    TP_Graphics_Texture_Destroy(viewport->colorTex);
    TP_Graphics_Texture_Destroy(viewport->depthTex);

    delete viewport;
}

void TP_Graphics_Viewport_BeginRender(TP_Graphics_Viewport* viewport)
{
    assert(activeViewport == nullptr);
    activeViewport = viewport;

    deviceContext->OMSetRenderTargets(1,
        viewport->renderTargetView.GetAddressOf(),
        viewport->depthStencilView.Get());
    deviceContext->RSSetViewports(1, &viewport->d3dViewport);
}

void TP_Graphics_Viewport_FinishRender(TP_Graphics_Viewport*)
{
    activeViewport = nullptr;
}

void TP_Graphics_ClearColor(const tp_u8 r, const tp_u8 g, const tp_u8 b)
{
    const float colorArray[4] = {
        static_cast<float>(r) / 255.0f,
        static_cast<float>(g) / 255.0f,
        static_cast<float>(b) / 255.0f,
        1.0f
    };
    deviceContext->ClearRenderTargetView(activeViewport->renderTargetView.Get(),colorArray);
    deviceContext->ClearDepthStencilView(activeViewport->depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

tp_u16 TP_Graphics_Viewport_GetWidth(const TP_Graphics_Viewport* viewport)
{
    return viewport->colorTex->width;
}

tp_u16 TP_Graphics_Viewport_GetHeight(const TP_Graphics_Viewport* viewport)
{
    return viewport->colorTex->height;
}
