/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_MEMORY_H
#define TEAPACKET_MEMORY_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned int TP_Memory_Init(void);
void TP_Memory_DeInit(void);

/**
 * Allocates data. Equivalent to malloc.
 * @param amount The amount of bytes to allocate
 * @return A pointer to the data allocated, or nullptr if the allocation failed.
 */
void* TP_MemAlloc(size_t amount);
/**
 * Reallocates data to a new size. Equivalent to realloc.
 * @param ptr The data to reallocate. Must have been previously allocated with TP_MemAlloc.
 * @param newSize The new size of the data.
 * @return A new pointer to the reallocated data.
 */
void* TP_ReAlloc(void* ptr, size_t newSize);
/**
 * Frees data allocated with TP_MemAlloc.
 * @param data The data to free. Must have been previously allocated with TP_MemAlloc.
 */
void TP_MemFree(void* data);

/**
 * Allocates bytes all set to 0. Equivalent the calloc(amount, 1);
 * @param amount The amount of bytes to allocate.
 * @return The allocated data.
 */
void* TP_MemAllocNull(size_t amount);

#ifdef __cplusplus
}
#endif
#endif
