#include <utility>

#include "glshadermixer/spirv_to_glsl.hpp"

#include "spirv_glsl.hpp"

std::string GLShaderMixer::ConvertSpirVToGLSL(SpirVData spirVData, const GLSMix_SrcContext* sourceContext, const GLSMix_TargetContext* targetContext)
{
    (void)sourceContext;
    spirv_cross::CompilerGLSL compiler{std::move(spirVData)};

    spirv_cross::CompilerGLSL::Options options{};
    options.version = GLSMix_GLVersion_ToNum(targetContext->version);
    options.es = targetContext->version.platform == GLSMix_TargetPlatform_GLES;
    options.enable_420pack_extension = false;

    compiler.set_common_options(options);

    return compiler.compile();
}
