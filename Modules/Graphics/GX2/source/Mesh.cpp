#include "TeaPacket/Graphics/Mesh/Mesh.hpp"

#include <cstring>

#include "TeaPacket/Graphics/Mesh/MeshParameters.hpp"
#include "TeaPacket/Graphics/PlatformMesh.hpp"

#include <gx2r/draw.h>

#include "TeaPacket/Logging/Logging.hpp"

using namespace TeaPacket::Graphics;

Mesh::Mesh(const MeshParameters& parameters):
    platformMesh(std::make_unique<PlatformMesh>())
{
    platformMesh->vertexDataInfo = parameters.vertexInfo;
    platformMesh->buffers.reserve(parameters.vertexInfo.size());

    size_t vertexSize = 0;
    for (const auto& vertInfo : parameters.vertexInfo)
    {
        vertexSize += vertInfo.GetSize();
    }
    const size_t vertexCount = parameters.vertexData.size / vertexSize;
    size_t paramOffset = 0;
    
    for (const auto& vertInfo : parameters.vertexInfo)
    {
        size_t sizeOfElem = vertInfo.GetSize();
        GX2RBuffer& buffer = platformMesh->buffers.emplace_back(GX2RBuffer{
            .flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ,
            .elemSize = sizeOfElem,
            .elemCount = vertexCount,
            .buffer = nullptr
        });
        GX2RCreateBuffer(&buffer);
        auto* uploadBuffer = static_cast<unsigned char*>(GX2RLockBufferEx(&buffer, GX2R_RESOURCE_BIND_NONE));
        const auto* bufferSourceData = static_cast<unsigned char*>(parameters.vertexData.data) + paramOffset;
        
        for (size_t i = 0; i < vertexCount; i++)
        {
            memcpy(uploadBuffer, bufferSourceData, sizeOfElem);
            uploadBuffer += sizeOfElem;
            bufferSourceData += vertexSize;
        }
        paramOffset += buffer.elemSize;

        GX2RUnlockBufferEx(&buffer, GX2R_RESOURCE_BIND_NONE);
    }

    if (parameters.flags.useIndices)
    {
        assert(parameters.indices.has_value());
        platformMesh->indexBuffer.reserve(parameters.indices->size);
        // Copy index data in to internal buffer
        for (const unsigned long index : parameters.indices.value())
        {
            platformMesh->indexBuffer.emplace_back(static_cast<uint32_t>(index));
        }
        platformMesh->indexCount = parameters.indices.value().size;
        //Log(platformMesh->indexCount);
    }
    
}

void Mesh::SetActive()
{
    for (unsigned int i = 0; i < platformMesh->vertexDataInfo.size(); i++)
    {
        GX2RSetAttributeBuffer(&platformMesh->buffers[i], i, platformMesh->buffers[i].elemSize, 0); 
    }
    activeMesh = this;
}

TP_OBJ_IMPL_DESTRUCTOR_MOVE_DEFAULT(Mesh);