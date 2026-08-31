#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/GS/Mesh.h"

namespace TeaPacket::Graphics::D3D11
{
    inline Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
    inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
    inline Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState = nullptr;

    inline TP_GfxGS_Mesh* activeMesh = nullptr;
}
