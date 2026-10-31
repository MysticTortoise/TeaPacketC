#include <spirv-tools/optimizer.hpp>

#include "glshadermixer/passes.hpp"
#include "passes/rename_inputs.hpp"
#include "passes/rename_outputs.hpp"
#include "passes/rename_samplers.hpp"
#include "passes/rename_uniforms.hpp"

#include "spvpass/pass.hpp"

#include <fstream>

#include "../../settings_core/include/glshadermixer/settings.h"


GLShaderMixer::SpirVData GLShaderMixer::TransformSpirv(const SpirVData& spirv_data,
                                                       const GLSMix_SrcContext* srcContext,
                                                       const GLSMix_TargetContext* targetContext)
{
    spvtools::Optimizer optimizer{SPV_ENV_OPENGL_4_5};

    {
        constexpr spv_target_env env = SPV_ENV_UNIVERSAL_1_0;
        const spvtools::SpirvTools tools{env};
        constexpr uint32_t options = SPV_BINARY_TO_TEXT_OPTION_INDENT | SPV_BINARY_TO_TEXT_OPTION_FRIENDLY_NAMES;
        std::string text;
        std::ofstream outfile{"disassembly.spirv"};
        std::cout << "writing disassembly...\n";
        if (tools.Disassemble(spirv_data, &text, options))
        {
            outfile << text;

        } else
        {
            outfile << "failed to compile.";
        }

        outfile.close();
    }

    if (srcContext->shaderType == GLSMix_ShaderType_Vertex &&
        GLSMix_GLVersion_ToNum(targetContext->version) < 330)
    {
        spvpass::RegisterCustomPass<SpirVPassRenameVertexInputs>(optimizer);
    }

    if (srcContext->shaderType == GLSMix_ShaderType_Fragment &&
        (   GLSMix_GLVersion_ToNum(targetContext->version) < 410
            ||
            TP_StrViewEq(srcContext->platform, "MacOS"))
        )
    {
        spvpass::RegisterCustomPass<SpirVPassRenameFragmentInputs>(optimizer);
    }

    if (srcContext->shaderType == GLSMix_ShaderType_Fragment &&
        GLSMix_GLVersion_ToNum(targetContext->version) < 330)
    {
        spvpass::RegisterCustomPass<SpirVPassRenameFragmentOutputs>(optimizer);
    }

    if (srcContext->shaderType == GLSMix_ShaderType_Vertex &&
        (   GLSMix_GLVersion_ToNum(targetContext->version) < 410
            ||
            TP_StrViewEq(srcContext->platform, "MacOS"))
        )
    {
        spvpass::RegisterCustomPass<SpirVPassRenameVertexOutputs>(optimizer);
    }

    if (GLSMix_GLVersion_ToNum(targetContext->version) < 420)
    {
        spvpass::RegisterCustomPass<SpirVPassRenameSamplers>(optimizer);
    }


    if (GLSMix_GLVersion_ToNum(targetContext->version) > 140 &&
        GLSMix_GLVersion_ToNum(targetContext->version) < 420)
    {
        spvpass::RegisterCustomPass<SpirVPassRenameUniforms>(optimizer);
    }

    std::cout << "Running passes:\n";
    for (const auto name : optimizer.GetPassNames())
    {
        std::cout << name << "\n";
    }


    SpirVData optimizedData{};
    optimizer.Run(spirv_data.data(), spirv_data.size(), &optimizedData);

    return optimizedData;
}
