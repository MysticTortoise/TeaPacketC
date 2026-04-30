#include "TeaPacket/Graphics/Display.h"

#include <gx2/context.h>
#include <gx2/display.h>
#include <gx2/event.h>
#include <gx2/mem.h>
#include <gx2/state.h>
#include <gx2/swap.h>

#include "GraphicsHeap/DisposableForegroundResource.hpp"
#include "GraphicsHeap/GraphicsHeap.hpp"
#include "TeaPacket/Graphics/PlatformViewport.hpp"
#include "TeaPacket/Graphics/Viewport.h"
#include "TeaPacket/Logging/Logging.h"


using namespace TeaPacket::Graphics::GX2;

static DisposableForegroundMemResource tvScanBuffer;
static TP_Graphics_Viewport* tvViewport;
static DisposableForegroundMemResource drcScanBuffer;
static TP_Graphics_Viewport* drcViewport;

static void AllocateTVScanBuffer(const DisposableForegroundMemResource* scanBuffer)
{
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU, scanBuffer->data, scanBuffer->GetSize());
    GX2SetTVBuffer(
        scanBuffer->data,
        scanBuffer->GetSize(),
        GX2_TV_RENDER_MODE_WIDE_720P,
        GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8,
        GX2_BUFFERING_MODE_DOUBLE);
}
static void AllocateDRCScanBuffer(const DisposableForegroundMemResource* scanBuffer)
{
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU, scanBuffer->data, scanBuffer->GetSize());
    GX2SetDRCBuffer(
        scanBuffer->data,
        scanBuffer->GetSize(),
        GX2_DRC_RENDER_MODE_DOUBLE,
        GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8,
        GX2_BUFFERING_MODE_DOUBLE);
}

void TP_Graphics_InitDefaultDisplays(TP_Graphics_DisplayParamList params)
{
    uint32_t size, _dump;
    (void)params;

    // TV
    GX2CalcTVSize(
        GX2_TV_RENDER_MODE_WIDE_720P,
        GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8,
        GX2_BUFFERING_MODE_DOUBLE,
        &size,
        &_dump);

    //HeapAllocForeground(size, GX2_SCAN_BUFFER_ALIGNMENT);
    if (!tvScanBuffer.Initialize(
        ForegroundBucket::Foreground,
        size,
        GX2_SCAN_BUFFER_ALIGNMENT,
        AllocateTVScanBuffer
    ))
    {
        TP_LogConstStr("COULDN'T ALLOC TV SCAN BUFFER.");
    }
    GX2SetTVScale(1280, 720);

    TP_Graphics_ViewportParams tvViewParams = {
        .width = 1280,
        .height = 720,
        .shaderUsable = false
    };
    tvViewport = TP_Graphics_Viewport_Create(&tvViewParams);


    // DRC
    const GX2DrcRenderMode drcRenderMode = GX2GetSystemDRCMode();
    GX2CalcDRCSize(
        drcRenderMode,
        GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8,
        GX2_BUFFERING_MODE_DOUBLE,
        &size,
        &_dump);

    if (!drcScanBuffer.Initialize(
        ForegroundBucket::Foreground,
        size,
        GX2_SCAN_BUFFER_ALIGNMENT,
        AllocateDRCScanBuffer
    ))
    {
        TP_LogConstStr("COULDN'T ALLOC GAMEPAD SCAN BUFFER");
    }
    GX2SetDRCScale(854, 480);

    TP_Graphics_ViewportParams drcViewParams = {
        .width = 1280,
        .height = 720,
        .shaderUsable = false
    };
    drcViewport = TP_Graphics_Viewport_Create(&drcViewParams);

    GX2SetSwapInterval(1);
}

void TP_Graphics_Display_WaitForVSync()
{
    uint32_t swapCount, flipCount;
    OSTime lastFlip, lastVsync;
    uint32_t waitCount = 0;

    while (true) {
        GX2GetSwapStatus(&swapCount, &flipCount, &lastFlip, &lastVsync);

        if (flipCount >= swapCount) {
            break;
        }

        if (waitCount >= 10) {
            break;
        }

        waitCount++;
        GX2WaitForVsync();
    }
}

void TP_Graphics_Display_PresentAll()
{
    GX2SwapScanBuffers();
    GX2Flush();
    GX2DrawDone();
    GX2SetTVEnable(TRUE);
    GX2SetDRCEnable(TRUE);
}
TP_Graphics_DisplayID TP_Graphics_Display_GetCount()
{
    return 2;
}

void TP_Graphics_Display_BeginRender(const TP_Graphics_DisplayID id)
{
    if (id == 0)
    {
        TP_Graphics_Viewport_BeginRender(tvViewport);
    } else
    {
        TP_Graphics_Viewport_BeginRender(drcViewport);
    }
}

void TP_Graphics_Display_FinishRender(TP_Graphics_DisplayID id)
{
    if (id == 0)
    {
        GX2CopyColorBufferToScanBuffer(&tvViewport->colorBuffer, GX2_SCAN_TARGET_TV);
    } else
    {
        GX2CopyColorBufferToScanBuffer(&drcViewport->colorBuffer, GX2_SCAN_TARGET_DRC);
    }
}

tp_u16 TP_Graphics_Display_GetWidth(TP_Graphics_DisplayID id)
{
    if (id == 0)
    {
        return tvViewport->colorBuffer.surface.width;
    } else
    {
        return drcViewport->colorBuffer.surface.width;
    }
}

tp_u16 TP_Graphics_Display_GetHeight(TP_Graphics_DisplayID id)
{
    if (id == 0)
    {
        return tvViewport->colorBuffer.surface.height;
    } else
    {
        return drcViewport->colorBuffer.surface.height;
    }
}
