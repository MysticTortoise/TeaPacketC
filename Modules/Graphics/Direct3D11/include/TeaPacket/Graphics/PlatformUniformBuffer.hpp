#pragma once

#include <wrl/client.h>
#include <d3d11.h>

struct TP_Graphics_ShaderBuffer
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> cbuffer;
    size_t size;
};