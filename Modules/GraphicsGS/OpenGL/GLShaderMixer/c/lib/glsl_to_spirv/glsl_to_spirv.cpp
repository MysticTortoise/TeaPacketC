#include "glshadermixer/glsl_to_spirv.hpp"

#include <iostream>

#include "glslang/Public/ResourceLimits.h"
#include "glslang/Public/ShaderLang.h"
#include "SPIRV/GlslangToSpv.h"

static constexpr EShLanguage GetGLSLangShaderFromType(const GLSMix_ShaderType shaderType)
{
    switch (shaderType)
    {
    case GLSMix_ShaderType_Fragment:
        return EShLangFragment;
    case GLSMix_ShaderType_Vertex:
        return EShLangVertex;
    default: return static_cast<EShLanguage>(0);
    }
}

GLShaderMixer::SpirVData GLShaderMixer::ConvertGLSLToSpirV(
    const std::string_view source,
    const GLSMix_SrcContext* sourceContext)
{

    glslang::InitializeProcess();


    const EShLanguage type = GetGLSLangShaderFromType(sourceContext->shaderType);
    const char* const codeSrc = source.data();
    const int codeSize = static_cast<int>(source.size());

    glslang::TShader shader{type};

    shader.setStringsWithLengths(&codeSrc, &codeSize, 1);
    shader.setEnvClient(glslang::EShClientOpenGL, glslang::EShTargetOpenGL_450);
    shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_0);

    const TBuiltInResource defaultBuiltinResource = *GetDefaultResources();
    if (!shader.parse(&defaultBuiltinResource,
        450,
        ECoreProfile,
        false,
        true,
        EShMsgDefault))
    {
        std::cerr << shader.getInfoLog() << "\n" << shader.getInfoDebugLog() << std::endl;
        return {};
    }
    glslang::TProgram program;
    program.addShader(&shader);

    if (!program.link(EShMsgDefault))
    {
        std::cerr << program.getInfoLog() << "\n" << shader.getInfoDebugLog() << std::endl;
        return {};
    }


    SpirVData spirv{};
    glslang::GlslangToSpv(*program.getIntermediate(type), spirv);
    glslang::FinalizeProcess();

    return spirv;
}
