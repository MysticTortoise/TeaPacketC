#ifndef LIBGLSHADERMIXER_GLSHADERMIXER_H
#define LIBGLSHADERMIXER_GLSHADERMIXER_H

#include "glshadermixer/settings.h"

#ifdef __cplusplus
extern "C"
{
#endif

TP_ByteArray GLSMix_MixDownShader(
    TP_StringView glslCode,
    const GLSMix_TargetContext* targetContext,
    const GLSMix_SrcContext* srcContext
    );

#ifdef __cplusplus
}
#endif

#endif //LIBGLSHADERMIXER_GLSHADERMIXER_H