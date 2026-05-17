#include "tests.h"

#include "TeaPacket/Graphics/Display.h"

static const TP_Graphics_DisplayParams dispParams = {
    1280,
    720,
};

static const TP_Graphics_DisplayParamList dispParamList = {
    &dispParams,
    1
};

#if GFXTESTS_ALLOWED >= 1
static tp_bool Init(void)
{
    static tp_bool hasLaunched = tp_false;
    if (!hasLaunched) {
        TP_Graphics_InitDefaultDisplays(dispParamList);
        hasLaunched = tp_true;
    }
    return tp_true;
}

static void Render(void)
{

}

static void DeInit(void)
{

}
#else
static tp_bool Init(void) {return tp_true;}
static void Render(void) {}
static void DeInit(void) {}
#endif


GfxTest CreateDisplayTest = {
    Init,
    Render,
    DeInit
};