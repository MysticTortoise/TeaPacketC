#include "TeaPacket/Graphics/Mesh/Mesh.h"

#include <cstring>

#include "TeaPacket/Graphics/PlatformMesh.hpp"

#include <gx2/draw.h>
#include <gx2r/draw.h>

static TP_Graphics_Mesh* activeMesh;

TP_Graphics_Mesh* TP_Graphics_Mesh_Create(const TP_Graphics_MeshParams* params)
{
    auto* mesh = new TP_Graphics_Mesh;

    mesh->vertexDataInfo = std::vector(params->vertexInfo.p, params->vertexInfo.p + params->vertexInfo.size);
    mesh->buffers.reserve(params->vertexInfo.size);

    size_t vertexSize = 0;
    for (size_t i = 0; i < params->vertexInfo.size; i++)
    {
        vertexSize += TP_Graphics_ShaderVar_GetSize(params->vertexInfo.p[i]);
    }
    const size_t vertexCount = params->vertexData.size / vertexSize;
    size_t paramOffset = 0;

    for (size_t i = 0; i < params->vertexInfo.size; i++)
    {

        const size_t sizeOfElem = TP_Graphics_ShaderVar_GetSize(params->vertexInfo.p[i]);
        GX2RBuffer& buffer = mesh->buffers.emplace_back(GX2RBuffer{
            .flags = GX2R_RESOURCE_BIND_VERTEX_BUFFER | GX2R_RESOURCE_USAGE_CPU_WRITE | GX2R_RESOURCE_USAGE_GPU_READ,
            .elemSize = sizeOfElem,
            .elemCount = vertexCount,
            .buffer = nullptr
        });
        GX2RCreateBuffer(&buffer);
        auto* uploadBuffer = static_cast<unsigned char*>(GX2RLockBufferEx(&buffer, GX2R_RESOURCE_BIND_NONE));
        const auto* bufferSourceData = params->vertexData.p + paramOffset;

        for (size_t j = 0; j < vertexCount; j++)
        {
            memcpy(uploadBuffer, bufferSourceData, sizeOfElem);
            uploadBuffer += sizeOfElem;
            bufferSourceData += vertexSize;
        }
        paramOffset += buffer.elemSize;

        GX2RUnlockBufferEx(&buffer, GX2R_RESOURCE_BIND_NONE);
    }

    if (params->indexList.size != 0)
    {
        static_assert(std::is_same_v<
            std::remove_cvref_t<decltype(mesh->indexBuffer[0])>,
            std::remove_cvref_t<decltype(params->indexList.p[0])>
            >);
        mesh->indexBuffer = std::vector(params->indexList.p, params->indexList.p + params->indexList.size);
        //Log(platformMesh->indexCount);
    } else
    {
        mesh->indexBuffer.resize(0);
    }

    return mesh;
}

void TP_Graphics_Mesh_Destroy(TP_Graphics_Mesh* mesh)
{
    delete mesh;
}

void TP_Graphics_Mesh_SetActive(TP_Graphics_Mesh* mesh)
{
    for (unsigned int i = 0; i < mesh->vertexDataInfo.size(); i++)
    {
        GX2RSetAttributeBuffer(&mesh->buffers[i], i, mesh->buffers[i].elemSize, 0);
    }
}

void TP_Graphics_DrawMesh()
{
    assert(activeMesh != nullptr);

    if (activeMesh->indexBuffer.size() != 0)
    {
        GX2DrawIndexedEx(
            GX2_PRIMITIVE_MODE_TRIANGLES,
            activeMesh->indexBuffer.size(),
            GX2_INDEX_TYPE_U32,
            activeMesh->indexBuffer.data(),
            0,
            1);
    }

}