/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* ShaderBuffers are groups of non-specific data that can be sent to a shader.
 * In other APIs they can be known as Uniform Buffers or Constant Buffers.
 */
#ifndef TEAPACKET_GRAPHICS_SHADERBUFFER_H
#define TEAPACKET_GRAPHICS_SHADERBUFFER_H

#include "TeaPacket/Graphics/ShaderBufferParams.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Graphics_ShaderBuffer TP_Graphics_ShaderBuffer;

/**
 * Creates a ShaderBuffer from the given parameters.
 * @return The created ShaderBuffer
 */
TP_Graphics_ShaderBuffer* TP_Graphics_ShaderBuffer_Create(const TP_Graphics_ShaderBufferParams*);
/**
 * Destroys a ShaderBuffer.
 */
void TP_Graphics_ShaderBuffer_Destroy(TP_Graphics_ShaderBuffer*);

/**
 * Gets the size of a Shader Buffer's data.
 * @return The size of the Shader Buffer's data, in bytes.
 */
size_t TP_Graphics_ShaderBuffer_GetSize(TP_Graphics_ShaderBuffer*);

/**
 * Updates data in a Shader Buffer at a given position.
 * @param data The beginning of the source data to send.
 * @param length The size of the source data to send.
 * @param offset The offset within the shader buffer to place this data.
 * @warning Sending data while a buffer is currently active or being drawn with is undefined behavior.
 * Always send data to a buffer BEFORE drawing anything with it.
 */
void TP_Graphics_ShaderBuffer_SendData(TP_Graphics_ShaderBuffer*,
                                       const void* data,
                                       size_t length,
                                       size_t offset);
/**
 * Binds a ShaderBuffer to a slot to a shader.
 * @details Slots correspond to the binding location of a ShaderBuffer in the shader language
 * (i.e. the binding location of a uniform block in GLSL)
 * @param slot The slot to bind this buffer to.
 */
void TP_Graphics_ShaderBuffer_SetActive(TP_Graphics_ShaderBuffer*,
                                        tp_u8 slot);



/**
 * Whether or not the data sent to the GPU through a ShaderBuffer must be endian swapped.
 *
 * @warning THIS MUST BE CHECKED AND ACCOUNTED FOR WHEN SENDING DATA TO A SHADERBUFFER!
 * FAILURE TO DO SO WILL CAUSE ERRORS ON SOME PLATFORMS!
 */
extern const tp_bool TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped;

#ifdef __cplusplus
}
#endif
#endif
