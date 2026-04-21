#include "TeaPacket/Logging/Logging.h"

#include <stdio.h>


tp_bool TP_Logging_Init(void)   {return tp_true;}
void    TP_Logging_DeInit(void) {}

void TP_LogString(const TP_StringView view)
{
    fwrite(view.p, sizeof(char), view.size, stdout);
}

#include "TeaPacket/Logging/AutoLoggingFuncs.h"