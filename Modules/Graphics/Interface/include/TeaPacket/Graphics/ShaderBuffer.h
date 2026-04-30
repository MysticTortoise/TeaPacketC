#ifndef TEAPACKET_GRAPHICS_SHADERBUFFER_H
#define TEAPACKET_GRAPHICS_SHADERBUFFER_H

#include "TeaPacket/Graphics/ShaderBufferParams.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TP_Graphics_ShaderBuffer TP_Graphics_ShaderBuffer;

TP_Graphics_ShaderBuffer* TP_Graphics_ShaderBuffer_Create(TP_Graphics_ShaderBufferParams*);
void TP_Graphics_ShaderBuffer_Destroy(TP_Graphics_ShaderBuffer*);

size_t TP_Graphics_ShaderBuffer_GetSize(TP_Graphics_ShaderBuffer*);

void TP_Graphics_ShaderBuffer_SendData(TP_Graphics_ShaderBuffer*, const void* data, size_t length, size_t offset);
void TP_Graphics_ShaderBuffer_SetActive(TP_Graphics_ShaderBuffer*, tp_u8 slot);



extern const tp_bool TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped;

#ifdef __cplusplus
}
#endif
#endif
