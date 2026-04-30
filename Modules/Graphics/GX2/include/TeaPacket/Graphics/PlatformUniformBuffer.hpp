#pragma once


struct TP_Graphics_ShaderBuffer
{
    TeaPacket::Graphics::GX2::MEM2Resource<void> data;
    size_t size;
};