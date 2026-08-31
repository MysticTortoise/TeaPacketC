#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/GS/Texture/Texture.h"

struct TP_GfxGS_Viewport
{
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;

    D3D11_VIEWPORT d3dViewport;

    TP_GfxGS_Texture* colorTex;
    TP_GfxGS_Texture* depthTex;
};

