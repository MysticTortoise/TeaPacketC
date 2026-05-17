#include "tests.h"

static tp_bool Init(void)
{
    return tp_true;
}

static void Render(void)
{

}

static void DeInit(void)
{

}

GfxTest BootTest = {
    Init,
    Render,
    DeInit
};