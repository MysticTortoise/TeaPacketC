#include "TeaPacket/Bundled/Init.h"
#include "TeaPacket/Bundled/DeInit.h"


#include "tests.h"

static size_t id = 0;

int main(void)
{

    const GfxTest* tests[GfxTests_MAX] = {
        &BootTest,
        &CreateDisplayTest,
        &PresentDisplayTest,
        &ClearColorTest,
        &ShadersMeshTest,
        &TextureTest,
        &ShaderBufferTest
    };
    size_t curTime = 0;


    if (!TP_Bundled_Init())
    {
        TP_Bundled_DeInit();
        return -1;
    }

    tests[id]->initFunc();

    while (TP_System_ShouldRun())
    {
        TP_System_Process();
        tests[id]->renderFunc();


        curTime++;
        if (curTime >= 100)
        {
            tests[id]->deInitFunc();
            curTime = 0;
            id++;
            id %= GFXTEST_COUNT;
            tests[id]->initFunc();
        }
    }


    TP_Bundled_DeInit();
    return 0;
}
