#pragma once

#include <gx2r/buffer.h>

#include <vector>

#include "TeaPacket/Graphics/Shader/ShaderVariable.hpp"

namespace TeaPacket::Graphics
{
    struct PlatformMesh
    {
        std::vector<GX2RBuffer> buffers;
        std::vector<uint32_t> indexBuffer;

        size_t indexCount = 0;

        std::vector<ShaderVariableType> vertexDataInfo;
    };
}
