#ifndef TEAPACKET_MEMORY_H
#define TEAPACKET_MEMORY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned int TP_Memory_Init(void);
void TP_Memory_DeInit(void);

void* TP_MemAlloc(size_t amount);
void* TP_ReAlloc(void* ptr, size_t newSize);
void TP_MemFree(void* data);

void* TP_MemAllocNull(size_t amount);

#ifdef __cplusplus
}
#endif
#endif
