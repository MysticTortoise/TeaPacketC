#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

struct TP_Graphics_Viewport
{
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;

    D3D11_VIEWPORT d3dViewport;

    TP_Graphics_Texture* colorTex;
    TP_Graphics_Texture* depthTex;
};

