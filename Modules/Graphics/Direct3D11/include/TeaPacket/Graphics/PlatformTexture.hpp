#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/Texture/Format.h"
#include "TeaPacket/Graphics/Texture/TextureParams.h"
#include "TeaPacket/Types/Numeric.h"


struct TP_Graphics_Texture
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D = nullptr;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState = nullptr;

    tp_u16 height, width;
    TP_Graphics_Texture_Format format;
};

namespace TeaPacket::Graphics::D3D11
{
    struct DTextureParms
    {
        bool renderTargetColor : 1;
        bool renderTargetDepth : 1;
    };

    TP_Graphics_Texture* MakeTexture(const TP_Graphics_TextureParams* params, DTextureParms dparams);
}
