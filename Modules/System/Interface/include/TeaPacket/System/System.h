/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#ifndef TEAPACKET_SYSTEM_H
#define TEAPACKET_SYSTEM_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "TeaPacket/Types/Numeric.h"

tp_bool TP_System_Init(void);
void TP_System_DeInit(void);

/**
 * Processes all necessary System functionalities.
 * @details This function should be called regularly (every frame) to work properly.
 */
void TP_System_Process(void);

/**
 * Determines whether the application should continue running or not.
 *
 * @details If false, the application has been signaled to quit and should respond appropriately.
 * @return Whether the application should run or not.
 */
tp_bool TP_System_ShouldRun(void);

#ifdef __cplusplus
}
#endif
#endif
