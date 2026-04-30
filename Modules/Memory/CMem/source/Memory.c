#include "TeaPacket/Memory/Memory.h"

#include "stdlib.h"

unsigned int TP_Memory_Init(void)
{
    return 1;
}

void TP_Memory_DeInit(void)
{
}

void* TP_MemAlloc(const size_t amount)
{
    return malloc(amount);
}

void* TP_ReAlloc(void* ptr, const size_t newSize)
{
    return realloc(ptr, newSize);
}

void TP_MemFree(void* data)
{
    free(data);
}

void* TP_MemAllocNull(const size_t amount)
{
    return calloc(amount, 1);
}
