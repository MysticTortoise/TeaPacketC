
#ifndef TEAPACKET_SYSTEM_H
#define TEAPACKET_SYSTEM_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Types/Numeric.h"

tp_bool TP_System_Init(void);
void TP_System_DeInit(void);

void TP_System_Process(void);

tp_bool TP_System_ShouldRun(void);

#ifdef __cplusplus
}
#endif
#endif
