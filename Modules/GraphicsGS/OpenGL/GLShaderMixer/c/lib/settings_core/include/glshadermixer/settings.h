#ifndef LIBGLSHADERMIXER_GLSHADERMIXER_SETTINGS_H
#define LIBGLSHADERMIXER_GLSHADERMIXER_SETTINGS_H

#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef tp_u8 GLSMix_TargetPlatform;
#define GLSMix_TargetPlatform_NONE 0
#define GLSMix_TargetPlatform_GLCORE 1
#define GLSMix_TargetPlatform_GLES 2

typedef enum
{
    GLSMix_ShaderType_Fragment,
    GLSMix_ShaderType_Vertex,
} GLSMix_ShaderType;

typedef struct
{
    GLSMix_TargetPlatform platform;
    tp_u8 major;
    tp_u8 minor;
    tp_u8 _;
} GLSMix_GLVersion;

typedef struct
{
    GLSMix_GLVersion version;
} GLSMix_TargetContext;

typedef struct
{
    GLSMix_ShaderType shaderType;
} GLSMix_SrcContext;

#define _(v) (v.major * 100 + v.minor * 10)

static inline unsigned int GLSMix_GLVersion_ToNum(GLSMix_GLVersion version)
{
    unsigned int v = version.major * 100 + version.minor * 10;

    if (version.platform == GLSMix_TargetPlatform_GLES && version.major == 2)
    {
        return 100;
    }
    if (version.major == 3 && version.minor < 3 && version.platform == GLSMix_TargetPlatform_GLCORE)
    {
        v -= 170;
    } else if (version.major == 2)
    {
        v -= 80;
    }
    return v;
}

#ifdef __cplusplus
}
#endif

#endif //LIBGLSHADERMIXER_GLSHADERMIXER_SETTINGS_H