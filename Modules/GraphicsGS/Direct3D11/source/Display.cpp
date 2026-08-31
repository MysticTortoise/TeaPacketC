/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Graphics/GS/Display.h"

#include <dxgi1_3.h>
#include <memory>
#include <vector>

#include "TeaPacket/Graphics/GS/DisplayParams.h"
#include "TeaPacket/Graphics/GS/Graphics.h"
#include "../include/TeaPacket/Graphics/GS/PlatformDisplay.hpp"
#include "../include/TeaPacket/Graphics/GS/PlatformTexture.hpp"
#include "../include/TeaPacket/Graphics/GS/PlatformViewport.hpp"
#include "TeaPacket/Graphics/GS/ViewportParams.h"
#include "TeaPacket/Graphics/GS/WindowsGraphics.hpp"
#include "TeaPacket/MacroUtils/StructUtils.h"
#include "TeaPacket/Graphics/GS/D3D11/WinMacro.hpp"
#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"

using namespace TeaPacket::Graphics::D3D11;

PlatformDisplay::PlatformDisplay(const TP_GfxGS_DisplayParams* const params)
{
    const auto windowParams = TP_Window_Params{
        .x = 0,
        .y = 0,
        .width = params->width,
        .height = params->height,
        .title = TP_StrViewFromConstStr("TeaPacket")
    };
    this->window = TP_Window_Create(&windowParams);

    DXGI_SWAP_CHAIN_DESC desc;
    ZeroStruct(desc);
    desc.Windowed = true;
    desc.BufferCount = 2;
    desc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.BufferDesc.Width = windowParams.width;
    desc.BufferDesc.Height = windowParams.height;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.OutputWindow = this->window->windowHandle;
    desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    Microsoft::WRL::ComPtr<IDXGIDevice3> dxgiDevice;
    CheckErrorWinCom(device.As(&dxgiDevice));

    Microsoft::WRL::ComPtr<IDXGIAdapter> adapter;
    Microsoft::WRL::ComPtr<IDXGIFactory> factory;

    CheckErrorWinCom(dxgiDevice->GetAdapter(adapter.GetAddressOf()));
    CheckErrorWinCom(adapter->GetParent(IID_PPV_ARGS(factory.GetAddressOf())));
    CheckErrorWinCom(
        factory->CreateSwapChain(device.Get(), &desc, &this->swapchain)
    );

    {
        auto viewportParams = TP_GfxGS_ViewportParams{
            .width = params->width,
            .height = params->height,
            .shaderUsable = tp_false
        };
        viewport = TP_GfxGS_Viewport_Create(&viewportParams);
    }

    CheckErrorWinCom(
        this->swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                   reinterpret_cast<LPVOID*>(viewport->colorTex->texture2D.ReleaseAndGetAddressOf()))
    );

    CheckErrorWinCom(
        device->CreateRenderTargetView(viewport->colorTex->texture2D.Get(), nullptr,
                                       viewport->renderTargetView.ReleaseAndGetAddressOf())
    );
}

static auto Displays = std::vector<PlatformDisplay>();

void TP_GfxGS_InitDefaultDisplays(TP_GfxGS_DisplayParamList params)
{
    for (size_t i = 0; i < params.size; i++)
    {
        auto* thisParams = &params.p[i];
        Displays.emplace_back(thisParams);
    }
}

void TP_GfxGS_D3D11_DestroyDisplays()
{
    Displays.clear();
}

void TP_GfxGS_Display_PresentAll(const tp_bool waitForVSync)
{
    for (const auto& display : Displays)
    {
        CheckErrorWinCom(display.swapchain->Present(waitForVSync ? 1 : 0, 0));
    }
}

TP_GfxGS_DisplayID TP_GfxGS_Display_GetCount()
{
    return static_cast<TP_GfxGS_DisplayID>(Displays.size());
}

static TP_GfxGS_DisplayID currentDisplay;

void TP_GfxGS_Display_BeginRender(const TP_GfxGS_DisplayID id)
{
    TP_GfxGS_Viewport_BeginRender(Displays[id].viewport);
    currentDisplay = id;
}

void TP_GfxGS_Display_FinishRender()
{
    TP_GfxGS_Viewport_FinishRender();
}

tp_u16 TP_GfxGS_Display_GetWidth(const TP_GfxGS_DisplayID display)
{
    return Displays[display].viewport->colorTex->width;
}

tp_u16 TP_GfxGS_Display_GetHeight(const TP_GfxGS_DisplayID display)
{
    return Displays[display].viewport->colorTex->height;
}
