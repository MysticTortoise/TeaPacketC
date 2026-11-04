//
// Created by Eli Tessier on 9/28/26.
//

#include "GLShaderMixer/glshadermixer.h"

#include <fstream>
#include <iostream>

#include "../spirv_to_glsl/include/glshadermixer/spirv_to_glsl.hpp"
#include "glshadermixer/glsl_to_spirv.hpp"
#include "glshadermixer/passes.hpp"

using namespace GLShaderMixer;

TP_ByteArray GLSMix_MixDownShader(const TP_StringView glslCode, const GLSMix_TargetContext* targetContext,
                                  const GLSMix_SrcContext* srcContext)
{

    const SpirVData raw_spirv = ConvertGLSLToSpirV(std::string_view{glslCode.p, glslCode.size}, srcContext);
    if (raw_spirv.empty())
    {
        return {};
    }

    const SpirVData transformed_spirv = TransformSpirv(raw_spirv, srcContext, targetContext);
    if (transformed_spirv.empty())
    {
        return {};
    }
    const std::string glsl = ConvertSpirVToGLSL(transformed_spirv, srcContext, targetContext);
    if (glsl.empty())
    {
        return {};
    }

    const TP_ByteArray outData = {
        static_cast<tp_byte*>(malloc(glsl.size())),
        glsl.size()
    };
    memcpy(outData.p, glsl.data(), outData.size);

    std::cout << "Shader Output: \n" << glsl << std::endl;

    return outData;
}
