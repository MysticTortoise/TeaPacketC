#include "TeaPacket/Graphics/Mesh/Mesh.h"
#include "TeaPacket/Graphics/PlatformMesh.hpp"

#include <d3d11.h>
#include <cassert>

#include "TeaPacket/Graphics/WindowsGraphics.hpp"
#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"

using namespace TeaPacket::Graphics::D3D11;

TP_Graphics_Mesh* TP_Graphics_Mesh_Create(const TP_Graphics_MeshParams* const params)
{
    auto* mesh = new TP_Graphics_Mesh;

    size_t vertexSize = 0;
    for (size_t i = 0; i < params->vertexInfo.size; i++)
    {
        vertexSize += TP_Graphics_ShaderVar_GetSize(params->vertexInfo.p[i]);
    }
    mesh->vertexSize = static_cast<UINT>(vertexSize);

    D3D11_BUFFER_DESC vertexBufferDesc;
    D3D11_SUBRESOURCE_DATA d3dVertexData;

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = static_cast<unsigned int>(params->vertexData.size);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    d3dVertexData.pSysMem = params->vertexData.p;
    d3dVertexData.SysMemPitch = 0;
    d3dVertexData.SysMemSlicePitch = 0;

    CheckErrorWinCom(
        device->CreateBuffer(&vertexBufferDesc, &d3dVertexData, mesh->vertexBuffer.GetAddressOf())
    );

    if (params->indexList.size != 0)
    {
        assert(params->indexList.p != nullptr);

        D3D11_BUFFER_DESC indexBufferDesc;
        indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
        indexBufferDesc.ByteWidth = static_cast<UINT>(params->indexList.size * sizeof(params->indexList.p[0]));
        indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
        indexBufferDesc.CPUAccessFlags = 0;
        indexBufferDesc.MiscFlags = 0;
        indexBufferDesc.StructureByteStride = 0;

        D3D11_SUBRESOURCE_DATA d3dIndexData;
        d3dIndexData.pSysMem = params->indexList.p;
        d3dIndexData.SysMemPitch = 0;
        d3dIndexData.SysMemSlicePitch = 0;

        CheckErrorWinCom(
            device->CreateBuffer(&indexBufferDesc, &d3dIndexData, mesh->indexBuffer.GetAddressOf())
        );

        mesh->indexCount = static_cast<UINT>(params->indexList.size);
    }

    return mesh;
}

void TP_Graphics_Mesh_SetActive(TP_Graphics_Mesh* const mesh)
{
    activeMesh = mesh;

    constexpr unsigned int offset = 0;
    deviceContext->IASetVertexBuffers(0, 1,
        mesh->vertexBuffer.GetAddressOf(), &mesh->vertexSize, &offset);

    if (mesh->indexBuffer != nullptr)
    {
        deviceContext->IASetIndexBuffer(mesh->indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
        deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
}

void TP_Graphics_Mesh_Destroy(TP_Graphics_Mesh* mesh)
{
    delete mesh;
}
