/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* ShaderBuffers are groups of non-specific data that can be sent to a shader.
 * In other APIs they can be known as Uniform Buffers or Constant Buffers.
 */
#ifndef TEAPACKET_GRAPHICS_GS_SHADERBUFFER_H
#define TEAPACKET_GRAPHICS_GS_SHADERBUFFER_H

#include "TeaPacket/Graphics/GS/ShaderBufferParams.h"
#include "TeaPacket/Graphics/GS/VariableType.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_GfxGS_ShaderBuffer TP_GfxGS_ShaderBuffer;

/**
 * Creates a ShaderBuffer from the given parameters.
 * @return The created ShaderBuffer
 */
TP_GfxGS_ShaderBuffer* TP_GfxGS_ShaderBuffer_Create(const TP_GfxGS_ShaderBufferParams*);
/**
 * Destroys a ShaderBuffer.
 */
void TP_GfxGS_ShaderBuffer_Destroy(TP_GfxGS_ShaderBuffer*);

/**
 * Gets the size of a Shader Buffer's data.
 * @return The size of the Shader Buffer's data, in bytes.
 */
size_t TP_GfxGS_ShaderBuffer_GetSize(TP_GfxGS_ShaderBuffer*);


void TP_GfxGS_ShaderBuffer_SendData(TP_GfxGS_ShaderBuffer*,
                                       const void* data,
                                       size_t offset,
                                       TP_GfxGS_VariableType dataType);

/**
 * Sends raw data to a ShaderBuffer.
 * @param data The beginning of the source data to send.
 * @param length The size of the source data to send.
 * @param offset The offset within the shader buffer to place this data.
 * @warning Sending data while a buffer is currently active or being drawn with is undefined behavior.
 * Always send data to a buffer BEFORE drawing anything with it.
 *
 * Additionally, the target platform may expect your data in a specific format (i.e. Endian Swapped)
 * Check your target platform for specific information.
 */
void TP_GfxGS_ShaderBuffer_SendRawData(TP_GfxGS_ShaderBuffer*,
                                       const void* data,
                                       size_t length,
                                       size_t offset);
/**
 * Binds a ShaderBuffer to a slot to a shader.
 * @details Slots correspond to the binding location of a ShaderBuffer in the shader language
 * (i.e. the binding location of a uniform block in GLSL)
 * @param slot The slot to bind this buffer to.
 */
void TP_GfxGS_ShaderBuffer_SetActive(TP_GfxGS_ShaderBuffer*,
                                        tp_u8 slot);



#ifdef __cplusplus
}
#endif
#endif
