#pragma once

#include "wrl/client.h"
#include <d3d11.h>

#include "TeaPacket/Types/Numeric.h"
#include "TeaPacket/Graphics/Texture/Format.h"


struct TP_Graphics_Texture
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D = nullptr;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResourceView = nullptr;
    Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState = nullptr;

    tp_u16 height, width;
    TP_Graphics_Texture_Format format;
};

