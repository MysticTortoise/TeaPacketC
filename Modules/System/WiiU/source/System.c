#include "TeaPacket/System/System.h"

#include <whb/proc.h>

tp_bool TP_System_Init()
{
    WHBProcInit();
    return tp_true;
}

void TP_System_DeInit()
{
    WHBProcShutdown();
}

void TP_System_Process()
{

}

tp_bool TP_System_ShouldRun()
{
    return WHBProcIsRunning();
}
