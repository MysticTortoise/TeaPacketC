#include "tests.h"

#include "TeaPacket/Graphics/GS/Display.h"
#include "TeaPacket/Graphics/GS/Graphics.h"

#include "TeaPacket/Graphics/GS/Mesh.h"
#include "TeaPacket/Graphics/GS/Shader.h"
#include "TeaPacket/Graphics/GS/ShaderBuffer.h"

#include "TeaPacket/Assets/Assets.h"
#include "TeaPacket/Memory/Memory.h"

#include "TeaPacket/Endianness/Endian.h"
#include "TeaPacket/Endianness/FloatingEndian.h"

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

static const TP_GfxGS_VariableType shaderVar = {
    TP_GfxGS_VariableBaseType_Float,
    2
};

static const TP_GfxGS_MeshParams meshParams = {
    {(tp_byte*)&vertData, sizeof(vertData)},
    {&shaderVar, 1},
    {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_GfxGS_Mesh* mesh;

static TP_GfxGS_ShaderParams shaderParams = {
    {0},
    {0},
    {&shaderVar, 1}
};
static TP_GfxGS_Shader* shader;

static const TP_GfxGS_VariableType varList = TP_GfxGS_VariableType_FVEC2;

static const TP_GfxGS_ShaderBufferParams bufParams = {
    0,
    {&varList, 1}
};
static TP_GfxGS_ShaderBuffer* sbuffer;

static tp_bool Init(void)
{
    const TP_StringView vertShaderPath = TP_StrViewFromConstStr("shaderbuffer.vert");
    const TP_StringView fragShaderPath = TP_StrViewFromConstStr("color.frag");

    const TP_String vertCode = TP_Assets_ReadTextAsset(vertShaderPath);
    const TP_String fragCode = TP_Assets_ReadTextAsset(fragShaderPath);

    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    mesh = TP_GfxGS_Mesh_Create(&meshParams);


    shader = TP_GfxGS_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    sbuffer = TP_GfxGS_ShaderBuffer_Create(&bufParams);

    assert(mesh != 0);
    assert(shader != 0);

    return tp_true;
}

static const TP_Gfx_Color8 clearCol = {0};

static void Render(void)
{
    TP_GfxGS_Display_BeginRender(0);

    TP_GfxGS_ClearColor(clearCol);

    static float pos[2] = {0, .1f};
    pos[0] = (pos[0] + .01f);
    while (pos[0] > 0.5f) {
        pos[0] -= 0.5f;
    }
    TP_GfxGS_ShaderBuffer_SendData(sbuffer, (void*)pos, 0, varList);

    TP_GfxGS_Mesh_SetActive(mesh);
    TP_GfxGS_Shader_SetActive(shader);
    TP_GfxGS_ShaderBuffer_SetActive(sbuffer, 0);
    TP_GfxGS_DrawMesh();

    TP_GfxGS_Display_FinishRender();
    TP_GfxGS_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_GfxGS_Mesh_Destroy(mesh);
    TP_GfxGS_Shader_Destroy(shader);
    TP_GfxGS_ShaderBuffer_Destroy(sbuffer);
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