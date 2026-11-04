#pragma once

#include <string>
#include <vector>

#include "glshadermixer/settings.h"
#include "glshadermixer/_core_internal.hpp"

namespace GLShaderMixer
{
    std::string ConvertSpirVToGLSL(SpirVData spirVData,
        const GLSMix_SrcContext* sourceContext,
        const GLSMix_TargetContext* targetContext);
}
