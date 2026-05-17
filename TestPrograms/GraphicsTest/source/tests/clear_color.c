#include "tests.h"

#include "TeaPacket/Graphics/Display.h"
#include "TeaPacket/Graphics/Graphics.h"


#if GFXTESTS_ALLOWED >= 3
static tp_bool Init(void)
{
    return tp_true;
}

static void Render(void)
{
    TP_Graphics_Display_BeginRender(0);

    static unsigned char i = 0;
    i = (i+3)%255;
    TP_Graphics_ClearColor(i, 0, 0);

    TP_Graphics_Display_FinishRender(0);
    TP_Graphics_Display_PresentAll(tp_true);
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