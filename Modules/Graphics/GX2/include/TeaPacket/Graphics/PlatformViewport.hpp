#pragma once

#include <GraphicsHeap/DisposableForegroundResource.hpp>
#include <gx2/surface.h>

struct TP_Graphics_Viewport
{
    GX2ColorBuffer colorBuffer;
    TeaPacket::Graphics::GX2::DisposableForegroundMemResource colorBufferImage;

    GX2DepthBuffer depthBuffer;
    TeaPacket::Graphics::GX2::DisposableForegroundMemResource depthBufferImage;
};
