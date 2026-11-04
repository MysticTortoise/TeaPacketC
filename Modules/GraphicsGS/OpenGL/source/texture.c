#include "TeaPacket/Graphics/GS/Texture/Texture.h"
#include "TeaPacket/Graphics/GS/PlatformTexture.h"

#include "TeaPacket/Graphics/GS/GL/Texture/WrapMode.gen"
#include  "TeaPacket/Graphics/GS/GL/Texture/Filter.gen"
#include  "TeaPacket/Graphics/GS/GL/Texture/FilterMip.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/Format.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/FormatLayout.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/FormatType.gen"

#include <stdlib.h>

#include "TeaPacket/Graphics/GS/Viewport.h"
#include "TeaPacket/Graphics/GS/PlatformViewport.h"

static GLint GLSetActiveTexAndStore(const GLuint tempID)
{
    GLint lastTex;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTex);
    glBindTexture(GL_TEXTURE_2D, tempID);
    return lastTex;
}

static GLint GLGetTexParam(const GLuint texID, const GLenum param)
{
    const GLint lastTex = GLSetActiveTexAndStore(texID);
    GLint x;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, param, &x);
    glBindTexture(GL_TEXTURE_2D, lastTex);
    return x;
}

TP_GfxGS_Texture* TP_GfxGS_Texture_Create(const TP_GfxGS_TextureParams* params)
{
    TP_GfxGS_Texture* tex = malloc(sizeof(TP_GfxGS_Texture));
    const GLint wrapMode = TP_GfxGS_Texture_WrapModeToGL(params->wrapMode);
    glGenTextures(1, &tex->id);
    glBindTexture(GL_TEXTURE_2D, tex->id);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TP_GfxGS_Texture_FilterModeToGLMip(params->filterMode));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TP_GfxGS_Texture_FilterModeToGL(params->filterMode));

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        TP_Gfx_Image_FormatToGL(params->imageData.format),
        params->imageData.width,
        params->imageData.height,
        0,
        TP_Gfx_Image_FormatToGLLayout(params->imageData.format),
        TP_Gfx_Image_FormatToGLType(params->imageData.format),
        params->imageData.data
        );
    glGenerateMipmap(GL_TEXTURE_2D);

    return tex;
}

void TP_GfxGS_Texture_Destroy(TP_GfxGS_Texture* tex)
{
    glDeleteTextures(1, &tex->id);
    free(tex);
}

tp_u16 TP_GfxGS_Texture_GetWidth(TP_GfxGS_Texture* const tex)
{
    return (tp_u16)GLGetTexParam(tex->id, GL_TEXTURE_WIDTH);
}

tp_u16 TP_GfxGS_Texture_GetHeight(TP_GfxGS_Texture* const tex)
{
    return (tp_u16)GLGetTexParam(tex->id, GL_TEXTURE_HEIGHT);
}

TP_Gfx_Image_Format TP_GfxGS_Texture_GetFormat(TP_GfxGS_Texture* const tex)
{
    const GLint format = GLGetTexParam(tex->id, GL_TEXTURE_INTERNAL_FORMAT);
    return GLToTP_Gfx_Image_Format(format);
    // TODO: Is this correct? What about layouts? Etc?
}

void TP_GfxGS_Texture_SetActive(TP_GfxGS_Texture* const texture, tp_u8 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

tp_bool TP_GfxGS_Texture_IsFormatSupported(TP_Gfx_Image_Format format)
{
    return TP_Gfx_Image_FormatConvertableToGL(format);
}


tp_u16 TP_GfxGS_Viewport_GetWidth(TP_GfxGS_Viewport* viewport)
{
    return (tp_u16)GLGetTexParam(viewport->colorTex, GL_TEXTURE_WIDTH);
}

tp_u16 TP_GfxGS_Viewport_GetHeight(TP_GfxGS_Viewport* viewport)
{
    return (tp_u16)GLGetTexParam(viewport->colorTex, GL_TEXTURE_HEIGHT);
}
