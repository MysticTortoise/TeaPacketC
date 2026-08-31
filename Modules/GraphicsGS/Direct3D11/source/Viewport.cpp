/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/Viewport.h"

#include <cassert>
#include <d3d11.h>
#include <iostream>

#include "TeaPacket/Graphics/GS/Graphics.h"
#include "TeaPacket/Graphics/GS/PlatformTexture.hpp"
#include "TeaPacket/Graphics/GS/PlatformViewport.hpp"
#include "TeaPacket/Graphics/GS/ViewportParams.h"
#include "TeaPacket/Graphics/GS/WindowsGraphics.hpp"
#include "TeaPacket/Graphics/Common/ImageFormat.h"
#include "TeaPacket/Graphics/GS/Texture/Texture.h"
#include "TeaPacket/Graphics/GS/Texture/TextureParams.h"
#include "TeaPacket/MacroUtils/StructUtils.h"
#include "TeaPacket/Graphics/GS/D3D11/WinMacro.hpp"

using namespace TeaPacket::Graphics::D3D11;

TP_GfxGS_Viewport* TP_GfxGS_Viewport_Create(const TP_GfxGS_ViewportParams* params)
{
    auto* viewport = new TP_GfxGS_Viewport;

    {
        auto texParms = TP_GfxGS_TextureParams{
            .imageData = {
                .data = nullptr,
                .pitch = 0,
                .width = params->width,
                .height = params->height,
                .format = TP_Gfx_Image_Format_BGRA8,
            },
            .filterMode = TP_GfxGS_Texture_FilterMode_Linear,
            .wrapMode = TP_GfxGS_Texture_WrapMode_Wrap,
            .flags = {
                .shaderResource = params->shaderUsable,
                .cpuReadable = true,
                .writeMode = TP_GfxGS_Texture_AvailableMode_GPU,
            }
        };
        viewport->colorTex = MakeTexture(&texParms, {
            .renderTargetColor = true,
            .renderTargetDepth = false
        });
    }
    {
        auto texParms = TP_GfxGS_TextureParams{
            .imageData = {
                .data = nullptr,
                .pitch = 0,
                .width = params->width,
                .height = params->height,
                .format = TP_Gfx_Image_Format_D24S8
            },
            .filterMode = TP_GfxGS_Texture_FilterMode_Linear,
            .wrapMode = TP_GfxGS_Texture_WrapMode_Wrap,
            .flags = {
                .shaderResource = params->shaderUsable,
                .cpuReadable = true,
                .writeMode = TP_GfxGS_Texture_AvailableMode_GPU,
            }
        };
        viewport->depthTex = MakeTexture(&texParms, {
            .renderTargetColor = false,
            .renderTargetDepth = true
        });
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

static TP_GfxGS_Viewport* activeViewport;

void TP_GfxGS_Viewport_Destroy(const TP_GfxGS_Viewport* viewport)
{
    TP_GfxGS_Texture_Destroy(viewport->colorTex);
    TP_GfxGS_Texture_Destroy(viewport->depthTex);

    delete viewport;
}

void TP_GfxGS_Viewport_BeginRender(TP_GfxGS_Viewport* viewport)
{
    assert(activeViewport == nullptr);
    activeViewport = viewport;

    deviceContext->OMSetRenderTargets(1,
        viewport->renderTargetView.GetAddressOf(),
        viewport->depthStencilView.Get());
    deviceContext->RSSetViewports(1, &viewport->d3dViewport);
}

void TP_GfxGS_Viewport_FinishRender()
{
    activeViewport = nullptr;
}

void TP_GfxGS_ClearColor(TP_Gfx_Color8 color)
{
    const float colorArray[4] = {
        static_cast<float>(color.r) / 255.0f,
        static_cast<float>(color.g) / 255.0f,
        static_cast<float>(color.b) / 255.0f,
        1.0f
    };
    deviceContext->ClearRenderTargetView(activeViewport->renderTargetView.Get(),colorArray);
    deviceContext->ClearDepthStencilView(activeViewport->depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

tp_u16 TP_GfxGS_Viewport_GetWidth(const TP_GfxGS_Viewport* viewport)
{
    return viewport->colorTex->width;
}

tp_u16 TP_GfxGS_Viewport_GetHeight(const TP_GfxGS_Viewport* viewport)
{
    return viewport->colorTex->height;
}
