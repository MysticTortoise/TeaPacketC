#include "TeaPacket/Graphics/Shader/Shader.hpp"

#include <gx2/mem.h>
#include <gx2/shaders.h>

#include "TeaPacket/Graphics/PlatformShader.hpp"
#include "TeaPacket/Graphics/Shader/ShaderParameters.hpp"

#include "CafeGLSL/CafeGLSLCompiler.hpp"
#include "TeaPacket/Logging/Logging.hpp"

#include "ShaderAttributeFormat.hpp"
#include "GraphicsHeap/MEM2Resource.hpp"

using namespace TeaPacket::Graphics;

Shader::Shader(const ShaderParameters& parameters):
platformShader(std::make_unique<PlatformShader>(PlatformShader{
    .vertexShader = nullptr,
    .pixelShader = nullptr,
    .fetchShader = GX2FetchShader(),
    .fetchShaderMemory = GX2::MEM2Resource<void>(GX2_SHADER_PROGRAM_ALIGNMENT, GX2CalcFetchShaderSizeEx(
            parameters.inputAttributes.size(),
            GX2_FETCH_SHADER_TESSELLATION_NONE,
            GX2_TESSELLATION_MODE_DISCRETE
        ))
}))
{
    // Compile vert shader
    char infoLog[1024];
    platformShader->vertexShader = std::unique_ptr<GX2VertexShader>(GLSL_CompileVertexShader(
        parameters.vertexShaderCode.c_str(),
        infoLog, sizeof(infoLog),
        GLSL_COMPILER_FLAG_NONE));
    if (!platformShader->vertexShader)
    {
        LogString("Failed to compile vertex shader:");
        throw std::runtime_error(std::string(infoLog, sizeof(infoLog)));
    }

    // Compile pixel shader
    platformShader->pixelShader = std::unique_ptr<GX2PixelShader>(GLSL_CompilePixelShader(
        parameters.fragmentShaderCode.c_str(),
        infoLog, sizeof(infoLog),
        GLSL_COMPILER_FLAG_NONE));
    
    if (!platformShader->pixelShader)
    {
        LogString("Failed to compile pixel shader:");
        throw std::runtime_error(std::string(infoLog, sizeof(infoLog)));
    }

    // Setup Fetch Shader
    std::vector<GX2AttribStream> attributeStreams;
    attributeStreams.reserve(parameters.inputAttributes.size());

    for (unsigned int i = 0; i < parameters.inputAttributes.size(); i++)
    {
        const auto& inputAttr = parameters.inputAttributes[i];
        const GX2AttribFormat format = GX2::GetGX2AttribFormatFromShaderVarType(inputAttr);
        attributeStreams.emplace_back(GX2AttribStream{
            .location = i,
            .buffer = i,
            .offset = 0,
            .format = format,
            .type = GX2_ATTRIB_INDEX_PER_VERTEX,
            .aluDivisor = 0,
            .mask = GX2::GfxGetAttribFormatSel(format),
            .endianSwap = GX2_ENDIAN_SWAP_DEFAULT
        });
    }

    GX2InitFetchShaderEx(
        &platformShader->fetchShader,
        static_cast<uint8_t*>(platformShader->fetchShaderMemory.get()),
        parameters.inputAttributes.size(),
        attributeStreams.data(),
        GX2_FETCH_SHADER_TESSELLATION_NONE,
        GX2_TESSELLATION_MODE_DISCRETE
        );

    // Invalidate shaders
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, platformShader->vertexShader->program, platformShader->vertexShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, platformShader->pixelShader->program, platformShader->pixelShader->size);
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_SHADER, platformShader->fetchShader.program, platformShader->fetchShader.size);
}

void Shader::SetActive()
{
    GX2SetFetchShader(&platformShader->fetchShader);
    GX2SetVertexShader(platformShader->vertexShader.get());
    GX2SetPixelShader(platformShader->pixelShader.get());
    GX2SetShaderMode(GX2_SHADER_MODE_UNIFORM_BLOCK);
    activeShader = this;
}


TP_OBJ_IMPL_DESTRUCTOR_MOVE_DEFAULT(Shader);

