#pragma once

#include <string_view>
#include <vector>

#include "glshadermixer/settings.h"
#include "glshadermixer/_core_internal.hpp"

namespace GLShaderMixer
{
    SpirVData ConvertGLSLToSpirV(std::string_view source, const GLSMix_SrcContext* sourceContext);
}
