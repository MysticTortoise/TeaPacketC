#include "tests.h"

#include "TeaPacket/Graphics/GS/Display.h"
#include "TeaPacket/Graphics/GS/Graphics.h"


#if GFXTESTS_ALLOWED >= 3
static tp_bool Init(void)
{
    return tp_true;
}

static void Render(void)
{
    TP_Gfx_Color8 c = {0};
    TP_GfxGS_Display_BeginRender(0);

    static unsigned char i = 0;
    i = (i+3)%255;
    c.r = i;
    TP_GfxGS_ClearColor(c);

    TP_GfxGS_Display_FinishRender();
    TP_GfxGS_Display_PresentAll(tp_true);
}

static void DeInit(void)
{

}
#else
static tp_bool Init(void) {return tp_true;}
static void Render(void) {}
static void DeInit(void) {}
#endif


GfxTest ClearColorTest = {
    Init,
    Render,
    DeInit
};