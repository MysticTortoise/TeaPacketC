#include "TeaPacket/Graphics/GS/Mesh.h"
#include "TeaPacket/Graphics/GS/Graphics.h"

#include "TeaPacket/Graphics/GS/PlatformMesh.h"
#include "TeaPacket/Graphics/GS/GL/GLVarType.gen"

#include <stdlib.h>

static TP_GfxGS_Mesh* currentMesh;

TP_GfxGS_Mesh* TP_GfxGS_Mesh_Create(const TP_GfxGS_MeshParams* params)
{
    TP_GfxGS_Mesh* mesh = malloc(sizeof(TP_GfxGS_Mesh));
    size_t vertexSize = 0;
    size_t vertexOffset = 0;

    for (size_t i = 0; i < params->vertexInfo.size; i++)
    {
        vertexSize += TP_GfxGS_ShaderVar_GetSize(params->vertexInfo.p[i]);
    }

    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        (GLsizeiptr)params->vertexData.size,
        params->vertexData.p,
        GL_STATIC_DRAW);

    if (params->indexList.size != 0)
    {
        glGenBuffers(1, &mesh->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            (GLsizeiptr)(params->indexList.size * sizeof(tp_u32)),
            params->indexList.p,
            GL_STATIC_DRAW);

        mesh->drawCount = (GLsizei)params->indexList.size;
    } else
    {
        mesh->EBO = 0;
        mesh->drawCount = (GLsizei)(params->vertexData.size / vertexSize);
    }

    for (size_t i = 0; i < params->vertexInfo.size; i++)
    {
        const TP_GfxGS_VariableType vType = params->vertexInfo.p[i];

        glVertexAttribPointer(
            i,
            vType.amount,
            TP_GfxGS_VariableBaseTypeToGL(vType.baseType),
            GL_FALSE,
            (GLsizei)vertexSize,
            (void*)vertexOffset
            );
        glEnableVertexAttribArray(i);

        vertexOffset += TP_GfxGS_ShaderVar_GetSize(vType);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return mesh;
}

void TP_GfxGS_Mesh_Destroy(TP_GfxGS_Mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    free(mesh);
}

void TP_GfxGS_Mesh_SetActive(TP_GfxGS_Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    currentMesh = mesh;
}

void TP_GfxGS_DrawMesh(void)
{
    if (currentMesh->EBO)
    {
        glDrawElements(GL_TRIANGLES, currentMesh->drawCount, GL_UNSIGNED_INT, 0);
    } else
    {
        glDrawArrays(GL_TRIANGLES, 0, currentMesh->drawCount);
    }
}