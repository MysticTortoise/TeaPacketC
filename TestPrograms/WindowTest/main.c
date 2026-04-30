#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Graphics/DisplayParams.h"
#include "TeaPacket/Graphics/Display.h"

int main(void)
{
    const TP_Window_Params parms = {
        0,
        0,
        1280,
        720,
        TP_StrViewFromConstStr("TeaPacket")
    };
    TP_Window* window = TP_Window_Create(&parms);

    unsigned int i;
    for (i = 0; i < 2000000; i++)
    {
        TP_Window_ProcessEvents(window);
    }

    TP_Window_Destroy(window);

    return 0;
}