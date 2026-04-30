#pragma once

#include "GraphicsHeap/MEM2Resource.hpp"

#include <gx2/shaders.h>
#include <memory>


struct TP_Graphics_Shader
{
    std::unique_ptr<GX2VertexShader> vertexShader;
    std::unique_ptr<GX2PixelShader> pixelShader;

    GX2FetchShader fetchShader;
    TeaPacket::Graphics::GX2::MEM2Resource<void> fetchShaderMemory;
};
