/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Logging/Logging.h"

#include <iostream>


tp_bool TP_Logging_Init()   {return tp_true;}
void    TP_Logging_DeInit() {}

void TP_LogString(const TP_StringView view)
{
    std::cout.write(view.p, static_cast<std::streamsize>(view.size) * sizeof(char));
    std::cout << std::endl;
}

#include "TeaPacket/Logging/AutoLoggingFuncs.inc"