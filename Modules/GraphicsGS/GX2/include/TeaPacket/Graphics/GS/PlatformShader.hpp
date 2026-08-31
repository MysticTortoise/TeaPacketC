#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include "GraphicsHeap/MEM2Resource.hpp"

#include <gx2/shaders.h>

struct TP_GfxGS_Shader
{
    GX2VertexShader* vertexShader = nullptr;
    GX2PixelShader* pixelShader = nullptr;

    GX2FetchShader fetchShader;
    TeaPacket::Graphics::GX2::MEM2Resource<void> fetchShaderMemory;
};
