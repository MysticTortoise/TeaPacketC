#include "TeaPacket/Graphics/Shader/Shader.h"

#include <gx2/mem.h>
#include <gx2/shaders.h>

#include "TeaPacket/Graphics/PlatformShader.hpp"

#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "TeaPacket/Logging/Logging.h"

#include "ShaderAttributeFormat.hpp"
#include "GraphicsHeap/MEM2Resource.hpp"

using namespace TeaPacket::Graphics::GX2;

TP_Graphics_Shader* TP_Graphics_Shader_Create(TP_Graphics_ShaderParams* params)
{
    auto* shader = new TP_Graphics_Shader{
        .vertexShader = nullptr,
        .pixelShader = nullptr,
        .fetchShader = GX2FetchShader(),
        .fetchShaderMemory = MEM2Resource<void>(GX2_SHADER_PROGRAM_ALIGNMENT, GX2CalcFetchShaderSizeEx(
                params->inputAttributes.size,
                GX2_FETCH_SHADER_TESSELLATION_NONE,
                GX2_TESSELLATION_MODE_DISCRETE
            ))
    };

    char infoLog[1024];

    {
        // Compile vert shader
        const auto cStrCode = new char[params->vertexShaderCode.size+1];
        memcpy(cStrCode, params->vertexShaderCode.p, params->vertexShaderCode.size);
        cStrCode[params->vertexShaderCode.size] = '\0';

        shader->vertexShader = std::unique_ptr<GX2VertexShader>(GLSL_CompileVertexShader(
            cStrCode,
            infoLog, sizeof(infoLog),
            GLSL_COMPILER_FLAG_NONE));
        if (!shader->vertexShader)
        {
            TP_LogConstStr("Failed to compile vertex shader. See log for errors.");
            TP_LogCharN(infoLog, sizeof(infoLog));
            return nullptr;
        }

        delete[] cStrCode;
    }

    {
        // Compile pixel shader
        const auto cStrCode = new char[params->fragmentShaderCode.size+1];
        memcpy(cStrCode, params->fragmentShaderCode.p, params->fragmentShaderCode.size);
        cStrCode[params->fragmentShaderCode.size] = '\0';

        shader->pixelShader = std::unique_ptr<GX2PixelShader>(GLSL_CompilePixelShader(
            cStrCode,
            infoLog, sizeof(infoLog),
            GLSL_COMPILER_FLAG_NONE));
        if (!shader->pixelShader)
        {
            TP_LogConstStr("Failed to compile pixel shader. See log for errors.");
            TP_LogCharN(infoLog, sizeof(infoLog));
            return nullptr;
        }

        delete[] cStrCode;
    }

    // Setup Fetch Shader
    std::vector<GX2AttribStream> attributeStreams;
    attributeStreams.reserve(params->inputAttributes.size);

    for (unsigned int i = 0; i < params->inputAttributes.size; i++)
    {
        const auto& inputAttr = params->inputAttributes.p[i];
        const GX2AttribFormat format = GetGX2AttribFormatFromShaderVarType(inputAttr);
        attributeStreams.emplace_back(GX2AttribStream{
            .location = i,
            .buffer = i,
            .offset = 0,
            .format = format,
            .type = GX2_ATTRIB_INDEX_PER_VERTEX,
            .aluDivisor = 0,
            .mask = GfxGetAttribFormatSel(format),
            .endianSwap = GX2_ENDIAN_SWAP_DEFAULT
        });
    }

    GX2InitFetchShaderEx(
        &shader->fetchShader,
        static_cast<uint8_t*>(shader->fetchShaderMemory.get()),
        params->inputAttributes.size,
        attributeStreams.data(),
        GX2_FETCH_SHADER_TESSELLATION_NONE,
        GX2_TESSELLATION_MODE_DISCRETE
        );

    // Invalidate shaders
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, shader->vertexShader->program, shader->vertexShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, shader->pixelShader->program, shader->pixelShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, shader->fetchShader.program, shader->fetchShader.size);

    return shader;
}

void TP_Graphics_Shader_Destroy(TP_Graphics_Shader* shader)
{
    delete shader;
}

void TP_Graphics_Shader_SetActive(TP_Graphics_Shader* shader)
{
    GX2SetFetchShader(&shader->fetchShader);
    GX2SetVertexShader(shader->vertexShader.get());
    GX2SetPixelShader(shader->pixelShader.get());
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
}
