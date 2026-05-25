#include "tests.h"

#include "TeaPacket/Graphics/Display.h"
#include "TeaPacket/Graphics/Graphics.h"

#include "TeaPacket/Graphics/Mesh.h"
#include "TeaPacket/Graphics/Shader.h"
#include "TeaPacket/Graphics/Texture/Texture.h"


#include "TeaPacket/Assets/Assets.h"
#include "TeaPacket/Memory/Memory.h"

#include <assert.h>

#if GFXTESTS_ALLOWED >= 5

static const float vertData[] = {
    -0.5f, 0.5f, 0.0f, 0.0f,
     0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f,-0.5f, 0.0f, 1.0f,
     0.5f,-0.5f, 1.0f, 1.0f
};

static const tp_u32 faceData[] = {
    0, 1, 2,
    1, 3, 2
};

static const tp_byte texData[] = {
    255, 0, 0, 255, //red
    0, 255, 0, 255, //green
    0, 0, 255, 255, //blue
    255, 255, 0, 255, //yellow
    0, 255, 255, 255, // cyan
    255, 0, 255, 255, // magenta
    0, 0, 0, 255, // black
    128, 128, 128, 255, // grey
    255, 255, 255, 255 // white
};

static const TP_Graphics_VariableType shaderVars[] = {
{
        TP_Graphics_VariableBaseType_Float,
        2
    },
{
    TP_Graphics_VariableBaseType_Float,
    2
    }
};

static const TP_Graphics_MeshParams meshParams = {
    .vertexData = {(tp_byte*)&vertData, sizeof(vertData)},
    .vertexInfo =  {shaderVars, 2},
    .indexList = {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_Graphics_Mesh* mesh;

static TP_Graphics_ShaderParams shaderParams = {
    .vertexShaderCode = {0},
    .fragmentShaderCode = {0},
    .inputAttributes = {shaderVars, 2}
};
static TP_Graphics_Shader* shader;

static const TP_Graphics_TextureParams texParams = {
    .data = (void*)texData,
    .width = 3,
    .height = 3,
    .format = TP_Graphics_Texture_Format_RGBA8,
    .filterMode = TP_Graphics_Texture_FilterMode_Nearest,
    .wrapMode = TP_Graphics_Texture_WrapMode_Wrap,
    .flags = {
        .shaderResource = tp_true,
        .cpuReadable = tp_false,
        .writeMode = TP_Graphics_Texture_AvailableMode_None
    }
};
static TP_Graphics_Texture* texture;


static tp_bool Init(void)
{
    mesh = TP_Graphics_Mesh_Create(&meshParams);

    const TP_String vertCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.vert"));
    const TP_String fragCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.frag"));
    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    shader = TP_Graphics_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    texture = TP_Graphics_Texture_Create(&texParams);

    assert(mesh != 0);
    assert(shader != 0);
    assert(texture != 0);

    return tp_true;
}

static void Render(void)
{
    TP_Graphics_Display_BeginRender(0);

    TP_Graphics_ClearColor(0, 0, 0);

    TP_Graphics_Mesh_SetActive(mesh);
    TP_Graphics_Shader_SetActive(shader);
    TP_Graphics_Texture_SetActive(texture, 1);
    TP_Graphics_DrawMesh();

    TP_Graphics_Display_FinishRender();
    TP_Graphics_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_Graphics_Mesh_Destroy(mesh);
    TP_Graphics_Shader_Destroy(shader);
    TP_Graphics_Texture_Destroy(texture);
}
#else
static tp_bool Init(void) {return tp_true;}
static void Render(void) {}
static void DeInit(void) {}
#endif


GfxTest TextureTest = {
    Init,
    Render,
    DeInit
};