#include "tests.h"

#include "TeaPacket/Graphics/GS/Display.h"
#include "TeaPacket/Graphics/GS/Graphics.h"

#include "TeaPacket/Graphics/GS/Mesh.h"
#include "TeaPacket/Graphics/GS/Shader.h"
#include "TeaPacket/Graphics/GS/Texture/Texture.h"


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

static const TP_GfxGS_VariableType shaderVars[] = {
{
        TP_GfxGS_VariableBaseType_Float,
        2
    },
{
    TP_GfxGS_VariableBaseType_Float,
    2
    }
};

static const TP_GfxGS_MeshParams meshParams = {
    .vertexData = {(tp_byte*)&vertData, sizeof(vertData)},
    .vertexInfo =  {shaderVars, 2},
    .indexList = {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_GfxGS_Mesh* mesh;

static TP_GfxGS_ShaderParams shaderParams = {
    .vertexShaderCode = {0},
    .fragmentShaderCode = {0},
    .inputAttributes = {shaderVars, 2}
};
static TP_GfxGS_Shader* shader;

static const TP_GfxGS_TextureParams texParams = {
    .imageData = {
        .data = (void*)texData,
        .pitch = 3*4,
        .width = 3,
        .height = 3,
        .format = TP_Gfx_Image_Format_RGBA8,
    },
    .filterMode = TP_GfxGS_Texture_FilterMode_Nearest,
    .wrapMode = TP_GfxGS_Texture_WrapMode_Wrap,
    .flags = {
        .shaderResource = tp_true,
        .cpuReadable = tp_false,
        .writeMode = TP_GfxGS_Texture_AvailableMode_None
    }
};
static TP_GfxGS_Texture* texture;



static tp_bool Init(void)
{
    mesh = TP_GfxGS_Mesh_Create(&meshParams);


    const TP_String vertCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.vert"));
    const TP_String fragCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.frag"));
    shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
    shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);

    shader = TP_GfxGS_Shader_Create(&shaderParams);

    TP_MemFree(vertCode.p);
    TP_MemFree(fragCode.p);

    texture = TP_GfxGS_Texture_Create(&texParams);

    assert(mesh != 0);
    assert(shader != 0);
    assert(texture != 0);

    return tp_true;
}

static const TP_Gfx_Color8 clearCol = {0};

static void Render(void)
{
    TP_GfxGS_Display_BeginRender(0);

    TP_GfxGS_ClearColor(clearCol);

    TP_GfxGS_Mesh_SetActive(mesh);
    TP_GfxGS_Shader_SetActive(shader);
    TP_GfxGS_Texture_SetActive(texture, 1);
    TP_GfxGS_DrawMesh();

    TP_GfxGS_Display_FinishRender();
    TP_GfxGS_Display_PresentAll(tp_true);
}

static void DeInit(void)
{
    TP_GfxGS_Mesh_Destroy(mesh);
    TP_GfxGS_Shader_Destroy(shader);
    TP_GfxGS_Texture_Destroy(texture);
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