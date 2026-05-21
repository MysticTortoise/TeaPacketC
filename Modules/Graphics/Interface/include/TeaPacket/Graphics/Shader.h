/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Shaders are programs that determine how Meshes are drawn to the screen.
 * A Shader in TeaPacket is comprised of a Vertex and a Fragment shader. Both must exist for a Shader to compile.
 * As the Graphics Module is based on OpenGL/Direct3D, these shaders follow the same principles as there.
 */
#ifndef TEAPACKET_GRAPHICS_SHADER_H
#define TEAPACKET_GRAPHICS_SHADER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "ShaderParams.h"

typedef struct TP_Graphics_Shader TP_Graphics_Shader;

/**
 * Creates a shader via the given parameters.
 * @param params The parameters to use for the Shader's creation.
 * @return The created Shader.
 */
TP_Graphics_Shader* TP_Graphics_Shader_Create(const TP_Graphics_ShaderParams* params);
/**
 * Destroys a shader.
 */
void TP_Graphics_Shader_Destroy(TP_Graphics_Shader*);

/**
 * Sets this Shader to be the currently active Shader.
 *
 * @details The active Shader is the one used when drawing meshes. Only one Shader may be active at a time.
 * @warning Calling TP_Graphics_DrawMesh without any active Shader is undefined behavior.
 */
void TP_Graphics_Shader_SetActive(TP_Graphics_Shader*);

#ifdef __cplusplus
}
#endif
#endif
