#pragma once

#include <vector>

#include "glshadermixer/settings.h"
#include "glshadermixer/_core_internal.hpp"

namespace GLShaderMixer
{
    SpirVData TransformSpirv(const SpirVData& spirv_data,
                             const GLSMix_SrcContext* srcContext,
                             const GLSMix_TargetContext* targetContext);
}