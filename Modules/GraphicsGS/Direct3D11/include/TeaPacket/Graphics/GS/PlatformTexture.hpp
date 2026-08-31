#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <d3d11.h>
#include <wrl/client.h>

#include "TeaPacket/Graphics/Common/ImageFormat.h"
#include "TeaPacket/Graphics/GS/Texture/TextureParams.h"
#include "TeaPacket/Types/Numeric.h"


struct TP_GfxGS_Texture
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D = nullptr;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState = nullptr;

    tp_u16 height, width;
    TP_Gfx_Image_Format format;
};

namespace TeaPacket::Graphics::D3D11
{
    struct DTextureParms
    {
        bool renderTargetColor : 1;
        bool renderTargetDepth : 1;
    };

    TP_GfxGS_Texture* MakeTexture(const TP_GfxGS_TextureParams* params, DTextureParms dparams);
}
