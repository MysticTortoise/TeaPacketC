#include "tests.h"

#include "TeaPacket/Graphics/GS/Display.h"
#include "TeaPacket/Graphics/GS/Graphics.h"

#include "TeaPacket/Graphics/GS/Mesh.h"
#include "TeaPacket/Graphics/GS/Shader.h"

#include "TeaPacket/Assets/Assets.h"
#include "TeaPacket/Memory/Memory.h"

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
    .vertexData = {(tp_byte*)&vertData, sizeof(vertData)},
    .vertexInfo =  {&shaderVar, 1},
    .indexList = {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_GfxGS_Mesh* mesh;

static TP_GfxGS_ShaderParams shaderParams = {
    .vertexShaderCode = {0},
    .fragmentShaderCode = {0},
    .inputAttributes = {&shaderVar, 1}
};
static TP_GfxGS_Shader* shader;


static tp_bool Init(void)
{
    mesh = TP_GfxGS_Mesh_Create(&meshParams);

    const TP_String vertCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("color.vert"));
    const TP_String fragCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("color.frag"));
    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    shader = TP_GfxGS_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    assert(mesh != 0);
    assert(shader != 0);

    return tp_true;
}

static const TP_Gfx_Color8 clearCol = {0};


static void Render(void)
{
    TP_GfxGS_Display_BeginRender(0);

    TP_GfxGS_ClearColor(clearCol);

    TP_GfxGS_Mesh_SetActive(mesh);
    TP_GfxGS_Shader_SetActive(shader);
    TP_GfxGS_DrawMesh();

    TP_GfxGS_Display_FinishRender();
    TP_GfxGS_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_GfxGS_Mesh_Destroy(mesh);
    TP_GfxGS_Shader_Destroy(shader);
}
#else
static tp_bool Init(void) {return tp_true;}
static void Render(void) {}
static void DeInit(void) {}
#endif


GfxTest ShadersMeshTest = {
    Init,
    Render,
    DeInit
};