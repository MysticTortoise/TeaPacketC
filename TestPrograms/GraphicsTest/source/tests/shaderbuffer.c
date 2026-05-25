#include "tests.h"

#include "TeaPacket/Graphics/Display.h"
#include "TeaPacket/Graphics/Graphics.h"

#include "TeaPacket/Graphics/Mesh.h"
#include "TeaPacket/Graphics/Shader.h"
#include "TeaPacket/Graphics/ShaderBuffer.h"

#include "TeaPacket/Assets/Assets.h"
#include "TeaPacket/Memory/Memory.h"

#include "TeaPacket/Endianness/Endian.h"

#include <assert.h>

#if GFXTESTS_ALLOWED >= 4

static const float vertData[] = {
    -0.5f, 0.5f,
     0.5f, 0.5f,
    -0.5f,-0.5f,
     0.5f,-0.5f
};

static const tp_u32 faceData[] = {
    0, 1, 2,
    1, 3, 2
};

static const TP_Graphics_VariableType shaderVar = {
    TP_Graphics_VariableBaseType_Float,
    2
};

static const TP_Graphics_MeshParams meshParams = {
    {(tp_byte*)&vertData, sizeof(vertData)},
    {&shaderVar, 1},
    {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_Graphics_Mesh* mesh;

static TP_Graphics_ShaderParams shaderParams = {
    {0},
    {0},
    {&shaderVar, 1}
};
static TP_Graphics_Shader* shader;

static const TP_Graphics_ShaderBufferParams bufParams = {
    0,
    sizeof(float) * 2
};
static TP_Graphics_ShaderBuffer* sbuffer;

static tp_bool Init(void)
{
    const TP_StringView vertShaderPath = TP_StrViewFromConstStr("shaderbuffer.vert");
    const TP_StringView fragShaderPath = TP_StrViewFromConstStr("color.frag");

    const TP_String vertCode = TP_Assets_ReadTextAsset(vertShaderPath);
    const TP_String fragCode = TP_Assets_ReadTextAsset(fragShaderPath);

    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    mesh = TP_Graphics_Mesh_Create(&meshParams);


    shader = TP_Graphics_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    sbuffer = TP_Graphics_ShaderBuffer_Create(&bufParams);

    assert(mesh != 0);
    assert(shader != 0);

    return tp_true;
}

static void Render(void)
{
    TP_Graphics_Display_BeginRender(0);

    TP_Graphics_ClearColor(0, 0, 0);

    static float pos[2] = {0, .1f};
    pos[0] = (pos[0] + .01f);
    while (pos[0] > 0.5f) {
        pos[0] -= 0.5f;
    }
    if (TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped)
    {
        for (size_t i = 0; i < sizeof(pos) / sizeof(pos[0]); i++)
        {
            pos[i] = TP_SwapF32(pos[i]);
        }
    }
    TP_Graphics_ShaderBuffer_SendData(sbuffer, (void*)pos, sizeof(pos), 0);
    if (TP_Graphics_ShaderBuffer_ShouldBeEndianSwapped)
    {
        for (size_t i = 0; i < sizeof(pos) / sizeof(pos[0]); i++)
        {
            pos[i] = TP_SwapF32(pos[i]);
        }
    }

    TP_Graphics_Mesh_SetActive(mesh);
    TP_Graphics_Shader_SetActive(shader);
    TP_Graphics_ShaderBuffer_SetActive(sbuffer, 0);
    TP_Graphics_DrawMesh();

    TP_Graphics_Display_FinishRender();
    TP_Graphics_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_Graphics_Mesh_Destroy(mesh);
    TP_Graphics_Shader_Destroy(shader);
    TP_Graphics_ShaderBuffer_Destroy(sbuffer);
}
#else
static tp_bool Init(void) {return tp_true;}
static void Render(void) {}
static void DeInit(void) {}
#endif


GfxTest ShaderBufferTest = {
    Init,
    Render,
    DeInit
};