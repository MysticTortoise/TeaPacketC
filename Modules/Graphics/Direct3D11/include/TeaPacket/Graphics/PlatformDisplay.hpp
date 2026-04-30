#pragma once

#include <dxgi.h>

#include "TeaPacket/Graphics/Viewport.h"
#include "TeaPacket/Window/Window.h"
#include "wrl/client.h"

namespace TeaPacket::Graphics::D3D11
{
    struct PlatformDisplay
    {
        TP_Window* window;

        Microsoft::WRL::ComPtr<IDXGISwapChain> swapchain;

        TP_Graphics_Viewport* viewport;

        explicit PlatformDisplay(const TP_Graphics_DisplayParams* const params);
    };
}
