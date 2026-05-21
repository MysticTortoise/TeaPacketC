#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

struct TP_Graphics_ShaderBuffer
{
    Microsoft::WRL::ComPtr<ID3D11Buffer> cbuffer;
    size_t size;
};