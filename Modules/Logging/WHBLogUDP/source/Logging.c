/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Logging/Logging.h"

#include <string.h>
#include <whb/log_udp.h>
#include <whb/log_cafe.h>
#include <whb/log.h>

#include "TeaPacket/Memory/Memory.h"

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
    char* b = TP_MemAlloc(view.size + 1);
    memcpy(b, view.p, view.size);
    b[view.size] = '\0';
    WHBLogPrint(b);
    TP_MemFree(b);
}

#include "TeaPacket/Logging/AutoLoggingFuncs.inc"
