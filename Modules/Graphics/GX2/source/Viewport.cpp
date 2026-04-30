#include "TeaPacket/Graphics/Viewport.h"

#include <gx2/clear.h>
#include <gx2/context.h>
#include <gx2/mem.h>
#include <gx2/registers.h>

#include "GraphicsHeap/GraphicsHeap.hpp"
#include "TeaPacket/Graphics/PlatformViewport.hpp"
#include "TeaPacket/Logging/Logging.h"


using namespace TeaPacket::Graphics::GX2;

static TP_Graphics_Viewport* activeViewport = nullptr;

static void AllocateGX2Invalidate(const DisposableForegroundMemResource* resource)
{
    GX2Invalidate(
        GX2_INVALIDATE_MODE_CPU,
        resource->data,
        resource->GetSize());
}

TP_Graphics_Viewport* TP_Graphics_Viewport_Create(TP_Graphics_ViewportParams* params)
{
    auto* viewport = new TP_Graphics_Viewport{
        .colorBuffer = {
            .surface = GX2Surface{
                .dim = GX2_SURFACE_DIM_TEXTURE_2D,
                .width = params->width,
                .height = params->height,
                .depth = 1,
                .mipLevels = 1,
                .format = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8,
                .aa = GX2_AA_MODE1X,
                .use = GX2_SURFACE_USE_TEXTURE_COLOR_BUFFER_TV,
                .imageSize = 0,
                .image = nullptr,
                .mipmapSize = 0,
                .mipmaps = nullptr,
                .tileMode = GX2_TILE_MODE_DEFAULT,
                .swizzle = 0,
                .alignment = 0,
                .pitch = 0,
                .mipLevelOffset = {}
            },
            .viewMip = 0,
            .viewFirstSlice = 0,
            .viewNumSlices = 1,
            .aaBuffer = nullptr,
            .aaSize = 0,
            .regs = {}
        },
        .colorBufferImage = DisposableForegroundMemResource(),
        .depthBuffer = {
            .surface = GX2Surface{
                .dim = GX2_SURFACE_DIM_TEXTURE_2D,
                .width = params->width,
                .height = params->height,
                .depth = 1,
                .mipLevels = 1,
                .format = GX2_SURFACE_FORMAT_FLOAT_R32,
                .aa = GX2_AA_MODE1X,
                .use = GX2_SURFACE_USE_DEPTH_BUFFER,
                .imageSize = 0,
                .image = nullptr,
                .mipmapSize = 0,
                .mipmaps = nullptr,
                .tileMode = GX2_TILE_MODE_DEFAULT,
                .swizzle = 0,
                .alignment = 0,
                .pitch = 0,
                .mipLevelOffset = {}
            },
            .viewMip = 0,
            .viewFirstSlice = 0,
            .viewNumSlices = 1,
            .hiZPtr = nullptr,
            .hiZSize = 0,
            .depthClear = 1.0f,
            .stencilClear = 0,
            .regs = {}
        },
        .depthBufferImage = DisposableForegroundMemResource(),
    };

    GX2CalcSurfaceSizeAndAlignment(&viewport->colorBuffer.surface);
    GX2InitColorBufferRegs(&viewport->colorBuffer);

    GX2CalcSurfaceSizeAndAlignment(&viewport->depthBuffer.surface);
    GX2InitDepthBufferRegs(&viewport->depthBuffer);

    // Alloc color buffer
    if (!viewport->colorBufferImage.Initialize(
        ForegroundBucket::MEM1,
        viewport->colorBuffer.surface.imageSize,
        static_cast<int>(viewport->colorBuffer.surface.alignment),
        AllocateGX2Invalidate
    ))
    {
        TP_LogConstStr("Falied to allocate color buffer.");
        return nullptr;
    }
    viewport->colorBuffer.surface.image = viewport->colorBufferImage.data;


    // Alloc Depth Buffer
    if (!viewport->depthBufferImage.Initialize(
        ForegroundBucket::MEM1,
        viewport->depthBuffer.surface.imageSize,
        static_cast<int>(viewport->depthBuffer.surface.alignment),
        AllocateGX2Invalidate
    ))
    {
        TP_LogConstStr("Falied to allocate depth buffer.");
    }
    viewport->depthBuffer.surface.image = viewport->depthBufferImage.data;

    return viewport;
}

void TP_Graphics_Viewport_BeginRender(TP_Graphics_Viewport* viewport)
{
    activeViewport = viewport;
    GX2SetColorBuffer(&viewport->colorBuffer, GX2_RENDER_TARGET_0);
    GX2SetDepthBuffer(&viewport->depthBuffer);
    GX2SetViewport(0, 0,TP_Graphics_Viewport_GetWidth(viewport),TP_Graphics_Viewport_GetHeight(viewport),0.0f, 1.0f);
    GX2SetScissor(0, 0, TP_Graphics_Viewport_GetWidth(viewport),TP_Graphics_Viewport_GetHeight(viewport));
}

void TP_Graphics_Viewport_FinishRender(TP_Graphics_Viewport* viewport)
{
    (void)viewport;
    activeViewport = nullptr;
}

tp_u16 TP_Graphics_Viewport_GetWidth(TP_Graphics_Viewport* viewport)
{
    return viewport->colorBuffer.surface.width;
}

tp_u16 TP_Graphics_Viewport_GetHeight(TP_Graphics_Viewport* viewport)
{
    return viewport->colorBuffer.surface.height;
}

constexpr float CharTo1Factor = 1.0f/255.0f;

void TP_Graphics_ClearColor(tp_u8 r, tp_u8 g, tp_u8 b)
{
    assert(activeViewport != nullptr);
    GX2ClearColor(&activeViewport->colorBuffer,
        r * CharTo1Factor, g * CharTo1Factor, b * CharTo1Factor, 1.0f);
    GX2ClearDepthStencilEx(&activeViewport->depthBuffer,
        activeViewport->depthBuffer.depthClear,
        activeViewport->depthBuffer.stencilClear,
        GX2_CLEAR_FLAGS_DEPTH | GX2_CLEAR_FLAGS_STENCIL);
}


void TP_Graphics_Viewport_Destroy(const TP_Graphics_Viewport* viewport)
{
    delete viewport;
}
