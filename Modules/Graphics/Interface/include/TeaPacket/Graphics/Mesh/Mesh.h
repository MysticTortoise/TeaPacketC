#ifndef TEAPACKET_GRAPHICS_MESH_H
#define TEAPACKET_GRAPHICS_MESH_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Graphics/Mesh/MeshParams.h"

typedef struct TP_Graphics_Mesh TP_Graphics_Mesh;

TP_Graphics_Mesh* TP_Graphics_Mesh_Create(const TP_Graphics_MeshParams*);
void TP_Graphics_Mesh_Destroy(TP_Graphics_Mesh*);

void TP_Graphics_Mesh_SetActive(TP_Graphics_Mesh*);

#ifdef __cplusplus
}
#endif
#endif
