#include "TeaPacket/Logging/Logging.h"

#include <whb/log_udp.h>
#include <whb/log_cafe.h>
#include <whb/log.h>

tp_bool TP_Logging_Init(void)
{
    if (!WHBLogUdpInit())
        return tp_false;
    if (!WHBLogCafeInit())
        return tp_false;

    return tp_true;
}
void TP_Logging_DeInit(void)
{
    WHBLogUdpDeinit();
    WHBLogCafeDeinit();
}

void TP_LogString(const TP_StringView view)
{
    WHBLogPrintf("%.*s", view.size, view.p);
}
