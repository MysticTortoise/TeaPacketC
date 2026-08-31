/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include "GraphicsHeap/GraphicsHeap.hpp"


#include <coreinit/memexpheap.h>
#include <coreinit/memfrmheap.h>
#include <coreinit/memheap.h>
#include <proc_ui/procui.h>

using namespace TeaPacket::Graphics::GX2;
using namespace TeaPacket::Graphics::GX2::_impl;

static bool hasForeground = false;

#define GFX_FRAME_HEAP_TAG (0x123DECAF)

static uint32_t InitializeBuckets([[maybe_unused]] void* context)
{
    hasForeground = true;
    // Mostly copied from GfxHeapInitMEM1 in whb/gfx_heap.c
    
    MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);

    if (!MEMRecordStateForFrmHeap(heap, GFX_FRAME_HEAP_TAG))
    {
        return 1;
    }

    uint32_t size = MEMGetAllocatableSizeForFrmHeapEx(heap, 4);
    if (!size)
    {
        return 1;
    }

    void* base = MEMAllocFromFrmHeapEx(heap, size, 4);
    if (!base)
    {
        return 1;
    }

    GfxHeapMEM1 = MEMCreateExpHeapEx(base, size, 0);
    if (!GfxHeapMEM1)
    {
        return 1;
    }


    // Mostly copied frm GfxHeapInitForeground

    heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);

    size = MEMGetAllocatableSizeForFrmHeapEx(heap, 4);
    if (!size) {
        return 1;
    }

    base = MEMAllocFromFrmHeapEx(heap, size, 4);
    if (!base) {
        return 1;
    }

    GfxHeapForeground = MEMCreateExpHeapEx(base, size, 0);
    if (!GfxHeapForeground) {
        return 1;
    }
    return 0;
}

static uint32_t FreeBuckets([[maybe_unused]] void* context)
{
    if (!hasForeground)
    {
        return 0;
    }
    hasForeground = false;
    MEMHeapHandle heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_MEM1);
    if (GfxHeapMEM1)
    {
        MEMDestroyExpHeap(GfxHeapMEM1);
        GfxHeapMEM1 = nullptr;
    }
    if (!MEMFreeByStateToFrmHeap(heap, GFX_FRAME_HEAP_TAG))
    {
        return 1;
    };

    heap = MEMGetBaseHeapHandle(MEM_BASE_HEAP_FG);
    if (GfxHeapForeground)
    {
        MEMDestroyExpHeap(GfxHeapForeground);
        GfxHeapForeground = nullptr;
    }
    MEMFreeToFrmHeap(heap, MEM_FRM_HEAP_FREE_ALL);
    return 0;
}

void TeaPacket::Graphics::GX2::InitializeMemory()
{
    InitializeBuckets(nullptr);
    ProcUIRegisterCallback(
        PROCUI_CALLBACK_ACQUIRE,
        InitializeBuckets, nullptr,
        GX2_INITMEM1_PRIORITY);
    ProcUIRegisterCallback(
        PROCUI_CALLBACK_RELEASE,
        FreeBuckets, nullptr,
        GX2_INITMEM1_PRIORITY);
    ProcUIRegisterCallback(
        PROCUI_CALLBACK_EXIT,
        FreeBuckets, nullptr,
        GX2_INITMEM1_PRIORITY);

    SetupGX2R();
}

void TeaPacket::Graphics::GX2::DeInitializeMemory()
{
    FreeBuckets(nullptr);
    ProcUIClearCallbacks();
    DeInitGX2R();
}
