#include "tests.h"

#include "TeaPacket/Graphics/Display.h"
#include "TeaPacket/Graphics/Graphics.h"

#include "TeaPacket/Graphics/Mesh.h"
#include "TeaPacket/Graphics/Shader.h"

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

static const TP_Graphics_VariableType shaderVar = {
    TP_Graphics_VariableBaseType_Float,
    2
};

static const TP_Graphics_MeshParams meshParams = {
    .vertexData = {(tp_byte*)&vertData, sizeof(vertData)},
    .vertexInfo =  {&shaderVar, 1},
    .indexList = {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_Graphics_Mesh* mesh;

static TP_Graphics_ShaderParams shaderParams = {
    .vertexShaderCode = {0},
    .fragmentShaderCode = {0},
    .inputAttributes = {&shaderVar, 1}
};
static TP_Graphics_Shader* shader;


static tp_bool Init(void)
{
    mesh = TP_Graphics_Mesh_Create(&meshParams);

    const TP_String vertCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("color.vert"));
    const TP_String fragCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("color.frag"));
    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    shader = TP_Graphics_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    assert(mesh != 0);
    assert(shader != 0);

    return tp_true;
}

static void Render(void)
{
    TP_Graphics_Display_BeginRender(0);

    TP_Graphics_ClearColor(0, 0, 0);

    TP_Graphics_Mesh_SetActive(mesh);
    TP_Graphics_Shader_SetActive(shader);
    TP_Graphics_DrawMesh();

    TP_Graphics_Display_FinishRender(0);
    TP_Graphics_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_Graphics_Mesh_Destroy(mesh);
    TP_Graphics_Shader_Destroy(shader);
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