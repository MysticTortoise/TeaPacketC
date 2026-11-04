#include "TeaPacket/Graphics/GS/ShaderBuffer.h"
#include "TeaPacket/Graphics/GS/PlatformShaderBuffer.h"

#include <stdlib.h>



TP_GfxGS_ShaderBuffer* TP_GfxGS_ShaderBuffer_Create(const TP_GfxGS_ShaderBufferParams* const params)
{
    TP_GfxGS_ShaderBuffer* buffer = malloc(sizeof(TP_GfxGS_ShaderBuffer));

    size_t bufSize = 0;
    for (size_t i = 0; i < params->infoList.size; i++)
    {
        bufSize += TP_GfxGS_ShaderVar_GetSize(params->infoList.p[i]);
    }

    glGenBuffers(1, &buffer->id);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
    if (params->data)
    {
        glBufferData(GL_UNIFORM_BUFFER, (GLsizeiptr)bufSize, params->data, GL_DYNAMIC_DRAW);
    } else
    {
        glBufferData(GL_UNIFORM_BUFFER, (GLsizeiptr)bufSize, NULL, GL_DYNAMIC_DRAW);
    }
    /*glBindBuffer(GL_UUID_SIZE_EXT, 0);*/

    return buffer;
}

void TP_GfxGS_ShaderBuffer_Destroy(TP_GfxGS_ShaderBuffer* const buffer)
{
    glDeleteBuffers(1, &buffer->id);
    free(buffer);
}

size_t TP_GfxGS_ShaderBuffer_GetSize(TP_GfxGS_ShaderBuffer* buffer)
{
    GLint result;
    glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
    glGetBufferParameteriv(GL_UNIFORM_BUFFER, GL_BUFFER_SIZE, &result);
    return result;
}

void TP_GfxGS_ShaderBuffer_SendData(TP_GfxGS_ShaderBuffer* buffer, const void* data, size_t offset,
    TP_GfxGS_VariableType dataType)
{
    TP_GfxGS_ShaderBuffer_SendRawData(buffer, data, TP_GfxGS_ShaderVar_GetSize(dataType), offset);
}

void TP_GfxGS_ShaderBuffer_SendRawData(TP_GfxGS_ShaderBuffer* buffer, const void* data, size_t length, size_t offset)
{
    glBindBuffer(GL_UNIFORM_BUFFER, buffer->id);
    glBufferSubData(
        GL_UNIFORM_BUFFER,
        (GLintptr)offset,
        (GLsizeiptr)length,
        data
        );
}


void TP_GfxGS_ShaderBuffer_SetActive(TP_GfxGS_ShaderBuffer* buffer, tp_u8 slot)
{
    glBindBufferBase(GL_UNIFORM_BUFFER, slot, buffer->id);
}



