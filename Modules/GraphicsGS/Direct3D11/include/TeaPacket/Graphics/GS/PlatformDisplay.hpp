#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <dxgi.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/GS/Viewport.h"
#include "TeaPacket/Window/Window.h"

namespace TeaPacket::Graphics::D3D11
{
    struct PlatformDisplay
    {
        TP_Window* window;

        Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;

        TP_GfxGS_Viewport* viewport;

        explicit PlatformDisplay(const TP_GfxGS_DisplayParams* params);
    };
}
