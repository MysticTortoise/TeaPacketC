#include "TeaPacket/Graphics/GS/Texture/Texture.h"
#include "TeaPacket/Graphics/GS/PlatformTexture.h"

#include "TeaPacket/Graphics/GS/GL/Texture/WrapMode.gen"
#include  "TeaPacket/Graphics/GS/GL/Texture/Filter.gen"
#include  "TeaPacket/Graphics/GS/GL/Texture/FilterMip.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/Format.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/FormatLayout.gen"
#include "TeaPacket/Graphics/GS/GL/Texture/FormatType.gen"

#include <stdlib.h>

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

void TP_GfxGS_Texture_SetActive(TP_GfxGS_Texture* const texture, tp_u8 slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

