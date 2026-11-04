#include "TeaPacket/Graphics/GS/Viewport.h"
#include "TeaPacket/Graphics/GS/PlatformViewport.h"

#include "TeaPacket/Graphics/GS/GL/gl.h"
#include <stdlib.h>

#include "TeaPacket/Graphics/GS/Texture/Texture.h"

TP_GfxGS_Viewport* TP_GfxGS_Viewport_Create(const TP_GfxGS_ViewportParams* params)
{
    TP_GfxGS_Viewport* viewport = malloc(sizeof(TP_GfxGS_Viewport));
    glGenFramebuffers(1, &viewport->fbo);

    glGenTextures(1, &viewport->colorTex);
    glBindTexture(GL_TEXTURE_2D, viewport->colorTex);
    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        params->width,
        params->height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        0
        );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &viewport->depthTex);
    glBindRenderbuffer(GL_RENDERBUFFER, viewport->depthTex);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, params->width, params->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_RENDERBUFFER, viewport->depthTex);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, viewport->colorTex, 0);

    {
        static const GLenum drawBuffers = GL_COLOR_ATTACHMENT0;
        glDrawBuffers(1, &drawBuffers);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        return 0;
    }

    viewport->width = params->width;
    viewport->height = params->height;

    return viewport;
}

void TP_GfxGS_Viewport_Destroy(TP_GfxGS_Viewport* viewport)
{
    glDeleteTextures(1, &viewport->colorTex);
    glDeleteRenderbuffers(1, &viewport->depthTex);
    glDeleteFramebuffers(1, &viewport->fbo);

    free(viewport);
}

void TP_GfxGS_Viewport_BeginRender(TP_GfxGS_Viewport* viewport)
{
    glBindFramebuffer(GL_FRAMEBUFFER, viewport->fbo);
    glViewport(0, 0, viewport->width, viewport->height);
}

void TP_GfxGS_Viewport_FinishRender(void)
{
    /* Do nothing. */
}