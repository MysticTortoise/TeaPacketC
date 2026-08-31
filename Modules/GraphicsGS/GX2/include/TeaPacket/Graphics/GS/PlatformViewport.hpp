#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <gx2/surface.h>

#include <GraphicsHeap/DisposableForegroundResource.hpp>

struct TP_GfxGS_Viewport
{
    GX2ColorBuffer colorBuffer;
    TeaPacket::Graphics::GX2::DisposableForegroundMemResource colorBufferImage;

    GX2DepthBuffer depthBuffer;
    TeaPacket::Graphics::GX2::DisposableForegroundMemResource depthBufferImage;
};
