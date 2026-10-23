#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Types/Array.h"

#include "TeaPacket/System/System.h"
int main(void)
{
    const TP_Window_Params parms = {
        0,
        0,
        1280,
        720,
        TP_StrViewFromConstStrBrace("TeaPacket")
    };
    TP_Window* window;


    TP_System_Init();
    window = TP_Window_Create(&parms);

    while(TP_System_ShouldRun()){
        TP_System_Process();
        TP_Window_ProcessEvents(window);
    }

    TP_Window_Destroy(window);

    TP_System_DeInit();

    return 0;
}