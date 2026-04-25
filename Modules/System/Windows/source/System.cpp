#include "TeaPacket/System/System.h"

#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Window/Window.hpp"

tp_bool TP_System_Init(){ return tp_true; }
void TP_System_DeInit() {}

void TP_System_Process()
{
    const size_t windowCount = TP_Window_GetCount();
    for (size_t i = 0; i < windowCount; i++)
    {
        TP_Window_ProcessEvents(TP_Window_Get(i));
    }
}

tp_bool TP_System_ShouldRun()
{
    return !TP_Window::shouldQuit;
}

