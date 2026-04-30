#ifndef TEAPACKET_GRAPHICS_MESHPARAMS_H
#define TEAPACKET_GRAPHICS_MESHPARAMS_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Graphics/Shader/VariableType.h"

typedef TP_ArrayView(tp_u32) TP_Graphics_MeshIndexList;

typedef struct
{
    TP_ByteView vertexData;
    TP_Graphics_Shader_VarList vertexInfo;
    TP_Graphics_MeshIndexList indexList;

} TP_Graphics_MeshParams;

#endif
