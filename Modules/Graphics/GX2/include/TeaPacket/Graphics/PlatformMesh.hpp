#pragma once

#include <gx2r/buffer.h>

#include <vector>

#include "TeaPacket/Graphics/Shader/VariableType.h"

struct TP_Graphics_Mesh
{
    std::vector<GX2RBuffer> buffers;
    std::vector<uint32_t> indexBuffer;

    std::vector<TP_Graphics_Shader_VariableType> vertexDataInfo;
};