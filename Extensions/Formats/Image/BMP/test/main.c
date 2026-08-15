#include <assert.h>
#include <TeaPacket/Extensions/Format/Image/BMP.h>

#include "TeaPacket/Assets/Assets.h"
#include "TeaPacket/Bundled/Init.h"
#include "TeaPacket/Bundled/DeInit.h"

#include "TeaPacket/Graphics/Display.h"
#include "TeaPacket/Graphics/Mesh.h"
#include "TeaPacket/Graphics/MeshParams.h"
#include "TeaPacket/Graphics/Shader.h"
#include "TeaPacket/Graphics/VariableBaseType.h"
#include "TeaPacket/Graphics/VariableType.h"
#include "TeaPacket/Graphics/Texture/Texture.h"

#if TeaPacket_Window_Implemented
#include "TeaPacket/Window/Window.h"
#endif


TP_StringView images[] = {
    TP_StrViewFromConstStrBrace("g/pal1.bmp"),
    TP_StrViewFromConstStrBrace("g/pal1wb.bmp"),
    TP_StrViewFromConstStrBrace("g/pal1bg.bmp"),
    TP_StrViewFromConstStrBrace("q/pal1p1.bmp"),
    TP_StrViewFromConstStrBrace("q/pal2.bmp"),
    TP_StrViewFromConstStrBrace("q/pal2color.bmp"),
    TP_StrViewFromConstStrBrace("g/pal4.bmp"),
    TP_StrViewFromConstStrBrace("g/pal4gs.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8-0.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8gs.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8w126.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8w125.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8w124.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8topdown.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8offs.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8oversizepal.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8nonsquare.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8os2.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2-sz.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2-hs.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2sp.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2v2.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2v2-16.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2v2-sz.bmp"),
    TP_StrViewFromConstStrBrace("q/pal8os2v2-40sz.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8v4.bmp"),
    TP_StrViewFromConstStrBrace("g/pal8v5.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb16.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb16bfdef.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb16-565.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb16-565pal.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb16faketrns.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb16-231.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb16-3103.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba16-4444.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba16-5551.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba16-1924.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb24.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb24pal.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb24largepal.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb32.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb32bfdef.bmp"),
    TP_StrViewFromConstStrBrace("g/rgb32bf.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb32h52.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb32-xbgr.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb32fakealpha.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb32-111110.bmp"),
    TP_StrViewFromConstStrBrace("q/rgb32-7187.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32-1.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32-2.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32-1010102.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32-81284.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32-61754.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32abf.bmp"),
    TP_StrViewFromConstStrBrace("q/rgba32h56.bmp"),
};


size_t imgIndex = 0;
TP_Graphics_ImageData data = {0};

const TP_Graphics_DisplayParams displays = {
    480, 360
};
const TP_Graphics_DisplayParamList displayList = {
    &displays, 1
};

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
    {(tp_byte*)&vertData, sizeof(vertData)},
    {shaderVars, 2},
    {faceData, sizeof(faceData) / sizeof(faceData[0])}
};
static TP_Graphics_Mesh* mesh;

static TP_Graphics_ShaderParams shaderParams = {
    {0},
    {0},
    {shaderVars, 2}
};
static TP_Graphics_Shader* shader;

static TP_Graphics_TextureParams texParams = {
    {0},
    TP_Graphics_Texture_FilterMode_Nearest,
    TP_Graphics_Texture_WrapMode_Wrap,
     {
         tp_true,
         tp_false,
         TP_Graphics_Texture_AvailableMode_None
    }
};
static TP_Graphics_Texture* texture;

TP_Extensions_Formats_Image_BMP_ReadOptions opts = {
    0
};

int main()
{
    TP_Bundled_Init();
    
    TP_Graphics_InitDefaultDisplays(displayList);
    
    {
        const TP_String vertCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.vert"));
        const TP_String fragCode = TP_Assets_ReadTextAsset(TP_StrViewFromConstStr("textured.frag"));
        shaderParams.vertexShaderCode = TP_StrViewFromStr(vertCode);
        shaderParams.fragmentShaderCode = TP_StrViewFromStr(fragCode);
        shader = TP_Graphics_Shader_Create(&shaderParams);
        TP_MemFree(vertCode.p);
        TP_MemFree(fragCode.p);
    }
    
    mesh = TP_Graphics_Mesh_Create(&meshParams);
    
    assert(shader != 0);
    assert(mesh != 0);

    {
        while (TP_System_ShouldRun())
        {
            if (data.data != 0)
            {
                TP_MemFree(data.data);
                TP_Graphics_Texture_Destroy(texture);
            }
            data = TP_Extensions_Formats_Image_ReadBMPFromAsset(images[imgIndex], &opts);
            texParams.imageData = data;
            texture = TP_Graphics_Texture_Create(&texParams);
            assert(texture != 0);
            
#if TeaPacket_Window_Implemented
            TP_Window_SetTitle(TP_Window_Get(0), images[imgIndex]);
#endif
            TP_LogString(images[imgIndex]);
            
            do
            {
                TP_System_Process();
                
                TP_Graphics_Display_BeginRender(0);
                TP_Graphics_ClearColor(0, 0, 0);
                TP_Graphics_Mesh_SetActive(mesh);
                TP_Graphics_Shader_SetActive(shader);
                TP_Graphics_Texture_SetActive(texture, 1);  
                TP_Graphics_DrawMesh();
                
                TP_Graphics_Display_FinishRender();
                TP_Graphics_Display_PresentAll(tp_true);
                
                TP_Input_UpdateControllers();
                TP_Input_PollSlot(0);
            } while (!TP_Input_IsButtonPressed(0, TP_Input_Button_PAD_START) && !TP_Input_IsButtonPressed(0, TP_Input_Button_KEY_ENTER));
            imgIndex++;
            
            if (imgIndex >= (sizeof(images) / sizeof(images[0]))){
                break;
            }
            
            while (TP_Input_IsButtonPressed(0, TP_Input_Button_PAD_START) || TP_Input_IsButtonPressed(0, TP_Input_Button_KEY_ENTER))
            {
                TP_System_Process();
                TP_Input_UpdateControllers();
                TP_Input_PollSlot(0);
            }
            imgIndex %= (sizeof(images) / sizeof(images[0]));
        }
    }

    TP_Bundled_DeInit();

    return 0;
}