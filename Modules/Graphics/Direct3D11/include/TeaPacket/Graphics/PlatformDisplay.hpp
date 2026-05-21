#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <dxgi.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/Viewport.h"
#include "TeaPacket/Window/Window.h"

namespace TeaPacket::Graphics::D3D11
{
    struct PlatformDisplay
    {
        TP_Window* window;

        Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;

        TP_Graphics_Viewport* viewport;

        explicit PlatformDisplay(const TP_Graphics_DisplayParams* params);
    };
}
