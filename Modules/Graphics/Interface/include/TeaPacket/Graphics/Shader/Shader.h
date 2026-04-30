#ifndef TEAPACKET_GRAPHICS_SHADER_H
#define TEAPACKET_GRAPHICS_SHADER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Graphics/Shader/ShaderParams.h"

typedef struct TP_Graphics_Shader TP_Graphics_Shader;

TP_Graphics_Shader* TP_Graphics_Shader_Create(TP_Graphics_ShaderParams* params);
void TP_Graphics_Shader_Destroy(TP_Graphics_Shader*);

void TP_Graphics_Shader_SetActive(TP_Graphics_Shader*);

#ifdef __cplusplus
}
#endif
#endif
