#include "tests.h"

#include "TeaPacket/Graphics/GS/Display.h"



#if GFXTESTS_ALLOWED >= 2
static tp_bool Init(void)
{
    return tp_true;
}

static void Render(void)
{
    TP_GfxGS_Display_BeginRender(0);
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


GfxTest PresentDisplayTest = {
    Init,
    Render,
    DeInit
};