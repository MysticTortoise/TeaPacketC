/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include "GraphicsHeap/GraphicsHeap.hpp"

#include <cstdlib>

#include <coreinit/memexpheap.h>
#include <gx2r/mem.h>
#include <gx2r/resource.h>


using namespace TeaPacket::Graphics::GX2;
using namespace TeaPacket::Graphics::GX2::_impl;

static constexpr GX2RResourceFlags MEM1ResourceTypes =
    GX2R_RESOURCE_BIND_COLOR_BUFFER |
    GX2R_RESOURCE_BIND_DEPTH_BUFFER |
    GX2R_RESOURCE_BIND_SCAN_BUFFER |
    GX2R_RESOURCE_USAGE_FORCE_MEM1;

static bool ShouldGX2RResourceBeMEM1(const GX2RResourceFlags flags)
{
    return flags & MEM1ResourceTypes && !(flags & GX2R_RESOURCE_USAGE_FORCE_MEM2);
}

static void* GX2RAlloc(const GX2RResourceFlags flags, const uint32_t size, const uint32_t alignment)
{
    //TeaPacket::LogString("GX2RAlloc");
    const int adjustedAlignment = CorrectAlignment(alignment);

    if (ShouldGX2RResourceBeMEM1(flags))
    {
        return MEMAllocFromExpHeapEx(GfxHeapMEM1, size, adjustedAlignment);
    }
    // MEM2 Allocation
    return std::aligned_alloc(adjustedAlignment, size);
}

static void GX2RFree(const GX2RResourceFlags flags, void* block)
{
    //TeaPacket::LogString("GX2RFree");
    if (ShouldGX2RResourceBeMEM1(flags))
    {
        MEMFreeToExpHeap(GfxHeapMEM1, block);
        return;
    }
    std::free(block);
}

void _impl::SetupGX2R()
{
    GX2RSetAllocator(&GX2RAlloc, &GX2RFree);
}

void _impl::DeInitGX2R()
{
    GX2RSetAllocator(nullptr, nullptr);
}
