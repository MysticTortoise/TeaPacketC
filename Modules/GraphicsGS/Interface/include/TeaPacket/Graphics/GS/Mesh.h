/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* Meshes are pieces of geometry to be drawn to the screen.
 * They are collections of vertices (and optionally faces) that will be drawn with a Shader.
 */
#ifndef TEAPACKET_GRAPHICS_GS_MESH_H
#define TEAPACKET_GRAPHICS_GS_MESH_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "TeaPacket/Graphics/GS/MeshParams.h"

typedef struct TP_GfxGS_Mesh TP_GfxGS_Mesh;

/**
 * Creates a mesh with the parameters given.
 * @return The mesh created.
 */
TP_GfxGS_Mesh* TP_GfxGS_Mesh_Create(const TP_GfxGS_MeshParams*);
/**
 * Destroys a mesh.
 */
void TP_GfxGS_Mesh_Destroy(TP_GfxGS_Mesh*);

/**
 * Sets a Mesh to be the currently active Mesh.
 * @details Active Meshes send their vertex data to IN attributes in GLSL.
 * Only one Mesh may be active at a time.
 * @warning Calling TP_GfxGS_DrawMesh without any active Mesh is undefined behavior.
 */
void TP_GfxGS_Mesh_SetActive(TP_GfxGS_Mesh*);

#ifdef __cplusplus
}
#endif
#endif
