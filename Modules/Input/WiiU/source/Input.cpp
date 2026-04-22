#include "TeaPacket/Input/Input.h"

#include <vpad/input.h>

#include "stdlib.h"
#include "string.h"

#include "VPadCode.h"

tp_bool TP_Input_Init()
{
    VPADInit();
    return tp_true;
}

void TP_Input_DeInit()
{
    VPADShutdown();
}

void TP_Input_UpdateControllers()
{
    
}

void TP_Input_PollSlot(const TP_Input_Slot slot)
{
    if (slot == 0)
    {
        PollVPad();
    }
}

tp_bool TP_Input_IsConnected(const TP_Input_Slot slot)
{
    if (slot == 0)
    {
        return IsVPadConnected();
    }

    return tp_false;
}

tp_bool TP_Input_IsButtonPressed(const TP_Input_Slot slot, const TP_Input_Button button)
{
    if (slot == 0)
    {
        return IsVPadButtonPressed(button);
    }
    return tp_false;
}

tp_bool TP_Input_IsButtonSupported(const TP_Input_Slot slot, const TP_Input_Button button)
{
    if (slot == 0)
    {
        return IsVPadButtonSupported(button);
    }
    return tp_false;
}

float TP_Input_GetAxis(const TP_Input_Slot slot, const TP_Input_Axis axis)
{
    if (slot == 0)
    {
        return GetVPadAxisValue(axis);
    }
    return 0;
}

tp_bool TP_Input_IsAxisSupported(const TP_Input_Slot slot, const TP_Input_Axis axis)
{
    if (slot == 0)
    {
        return GetVPadAxisSupported(axis);
    }
    return tp_false;
}

TP_Input_Slot TP_Input_GetLastSlotPressed(const TP_Input_ControllerType typeFilter)
{
    (void)typeFilter;
    return 0; // FIX WHEN MORE CONTROLLERS ADDED
}

const char WiiUGamepadStr[] = "Wii U Gamepad";\
const TP_String emptyString = {0, 0};

TP_String TP_Input_GetControllerName(TP_Input_Slot slot)
{
    if (slot == 0)
    {
        TP_String str;
        str.size = sizeof(WiiUGamepadStr)-1;
        str.p = (char*)malloc(str.size);
        memcpy(str.p, WiiUGamepadStr, str.size);
        return str;
    }
    return emptyString;
}

TP_Input_Slot TP_Input_GetSlotCount()
{
    return 5;
}
