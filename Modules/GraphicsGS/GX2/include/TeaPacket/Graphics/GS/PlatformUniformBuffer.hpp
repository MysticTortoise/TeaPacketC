#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include "GraphicsHeap/MEM2Resource.hpp"

struct TP_GfxGS_ShaderBuffer
{
    TeaPacket::Graphics::GX2::MEM2Resource<void> data;
    size_t size;
};