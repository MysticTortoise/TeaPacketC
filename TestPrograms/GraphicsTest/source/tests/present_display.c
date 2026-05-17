#include "tests.h"

#include "TeaPacket/Graphics/Display.h"



#if GFXTESTS_ALLOWED >= 2
static tp_bool Init(void)
{
    return tp_true;
}

static void Render(void)
{
    TP_Graphics_Display_BeginRender(0);
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


GfxTest PresentDisplayTest = {
    Init,
    Render,
    DeInit
};