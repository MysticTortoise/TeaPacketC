#include "TeaPacket/Graphics/GS/Shader.h"
#include "TeaPacket/Graphics/GS/PlatformShader.h"

#include <stdlib.h>
#include <string.h>

#include "TeaPacket/Logging/Logging.h"

#define TP_GL_MANUAL_TEX_BINDING TP_GfxGS_GL_MajorVer < 4 || (TP_GfxGS_GL_MajorVer == 4 && TP_GfxGS_GL_MinorVer < 2)

#if TP_GL_MANUAL_TEX_BINDING
static tp_bool IsInit = tp_false;
static GLint MAX_TEXTURE_UNITS;
static char** TEXTURE_UNIFORM_STRINGS;
static const char TEXTURE_PREFIX_STR[] = {'t'};
#endif

/* https://stackoverflow.com/a/1068937 */
static int numPlaces (int n) {
    assert(n >= 0);
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    assert(0);
    return 0;
}


static void numToStr(unsigned long x, char* dest, const unsigned int digits)
{
    static const char CharList[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    unsigned int i = digits;
    while (1)
    {
        if (--i > digits)
            break;
        dest[i] = CharList[x % 10];
        x /= 10;
    }
    assert(x == 0);
}

static void InitShaderGlobalConsts(void)
{
    IsInit = tp_true;
#if TP_GL_MANUAL_TEX_BINDING /* Setup manual tex binding */
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &MAX_TEXTURE_UNITS);

    TEXTURE_UNIFORM_STRINGS = malloc(MAX_TEXTURE_UNITS * sizeof(void*));
    for (GLint i = 0; i < MAX_TEXTURE_UNITS; i++)
    {
        const int digits = numPlaces(i);
        char* text = malloc(sizeof(TEXTURE_PREFIX_STR) + digits + 1);
        TEXTURE_UNIFORM_STRINGS[i] = text;

        memcpy(text, TEXTURE_PREFIX_STR, sizeof(TEXTURE_PREFIX_STR));
        text += sizeof(TEXTURE_PREFIX_STR);
        numToStr(i, text, digits);
        text[digits] = '\0';
    }
#endif
}

TP_GfxGS_Shader* TP_GfxGS_Shader_Create(const TP_GfxGS_ShaderParams* params)
{
    if (!IsInit)
    {
        InitShaderGlobalConsts();
    }
    TP_GfxGS_Shader* shader = malloc(sizeof(TP_GfxGS_Shader));
    GLint length, success;
    GLuint vShader, fShader;


    vShader = glCreateShader(GL_VERTEX_SHADER);
    length = params->vertexShaderData.size;
    glShaderSource(vShader, 1, (const GLchar* const*)&params->vertexShaderData.p, &length);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        TP_StringView str;
        str.p = infoLog;
        str.size = 512;
        glGetShaderInfoLog(vShader, 512, 0, infoLog);
        TP_LogString(str);
        return NULL;
    }

    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    length = params->fragmentShaderData.size;
    glShaderSource(fShader, 1, (const GLchar* const*)&params->fragmentShaderData.p, &length);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        TP_StringView str;
        str.p = infoLog;
        str.size = 512;
        glGetShaderInfoLog(fShader, 512, 0, infoLog);
        TP_LogString(str);
        return NULL;
    }

    shader->program = glCreateProgram();
    glAttachShader(shader->program, vShader);
    glAttachShader(shader->program, fShader);
    glLinkProgram(shader->program);

    glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        TP_StringView str;
        str.p = infoLog;
        str.size = 512;
        glGetProgramInfoLog(shader->program, 512, 0, infoLog);
        TP_LogString(str);
        return NULL;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    /* TODO:
     * Vertex in attrs < 3.3
     */

#if TP_GL_MANUAL_TEX_BINDING
    for (GLint i = 0; i < MAX_TEXTURE_UNITS; i++)
    {
        glUniform1i(glGetUniformLocation(shader->program, TEXTURE_UNIFORM_STRINGS[i]), i);
    }
#endif


    return shader;
}

void TP_GfxGS_Shader_Destroy(TP_GfxGS_Shader* shader)
{
    glDeleteProgram(shader->program);
    free(shader);
}

void TP_GfxGS_Shader_SetActive(TP_GfxGS_Shader* shader)
{
    glUseProgram(shader->program);
}
