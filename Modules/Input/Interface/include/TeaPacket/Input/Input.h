
#ifndef TEAPACKET_INPUT_H
#define TEAPACKET_INPUT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Types/Array.h"
#include "limits.h"
#include "TeaPacket/Types/Numeric.h"
#include "TeaPacket/Input/Button.h"
#include "TeaPacket/Input/Axis.h"
#include "TeaPacket/Input/ControllerType.h"


typedef unsigned int TP_Input_Slot;
const TP_Input_Slot NoControllerSlot = INT_MAX;

tp_bool TP_Input_Init(void);
void TP_Input_DeInit(void);

void TP_Input_UpdateControllers(void);

void    TP_Input_PollSlot(TP_Input_Slot slot);

tp_bool TP_Input_IsConnected(       TP_Input_Slot slot);
tp_bool TP_Input_IsButtonPressed(   TP_Input_Slot slot, TP_Input_Button button);
float   TP_Input_GetAxis(           TP_Input_Slot slot, TP_Input_Axis axis);

tp_bool TP_Input_IsButtonSupported( TP_Input_Slot slot, TP_Input_Button button);
tp_bool TP_Input_IsAxisSupported(   TP_Input_Slot slot, TP_Input_Axis axis);

TP_String TP_Input_GetControllerName(TP_Input_Slot slot);

TP_Input_Slot TP_Input_GetLastSlotPressed(TP_Input_ControllerType typeFilter);
TP_Input_Slot TP_Input_GetSlotCount(void);


#ifdef __cplusplus
}
#endif
#endif
