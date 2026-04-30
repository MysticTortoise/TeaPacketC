#pragma once

#include "d3d11.h"
#include "wrl/client.h"

struct TP_Graphics_Mesh;

namespace TeaPacket::Graphics::D3D11
{
    inline Microsoft::WRL::ComPtr<ID3D11Device> device = nullptr;
    inline Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
    inline Microsoft::WRL::ComPtr<ID3D11RasterizerState> defaultRasterizerState = nullptr;

    inline TP_Graphics_Mesh* activeMesh = nullptr;
}