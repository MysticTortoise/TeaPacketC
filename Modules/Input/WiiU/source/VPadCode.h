// ReSharper disable once CppMissingIncludeGuard
#include "TeaPacket/Input/WiiU/VPadButtons.gen"

#include <vpad/input.h>

#include "TeaPacket/Input/Axis.h"
#include "TeaPacket/Logging/Logging.h"

static VPADStatus currentVPadStatus;
static uint16_t vpadXTouch;
static uint16_t vpadYTouch;

static void PollVPad()
{
    VPADReadError err;
    while (true)
    {
        VPADRead(VPAD_CHAN_0, &currentVPadStatus, 1, &err);
        switch (err)
        {
        case VPAD_READ_SUCCESS:
            VPADGetTPCalibratedPointEx(VPAD_CHAN_0, VPAD_TP_1920X1080, &currentVPadStatus.tpNormal, &currentVPadStatus.tpNormal);
            if (!(currentVPadStatus.tpNormal.validity & VPAD_INVALID_X))
            {
                vpadXTouch = currentVPadStatus.tpNormal.x;
            }
            if (!(currentVPadStatus.tpNormal.validity & VPAD_INVALID_Y))
            {
                vpadYTouch = currentVPadStatus.tpNormal.y;
            }
        case VPAD_READ_NO_SAMPLES:
        case VPAD_READ_INVALID_CONTROLLER:
            return;
        case VPAD_READ_BUSY:
            continue;
        case VPAD_READ_UNINITIALIZED:
        default:
            return;
        }
    }
}

static tp_bool IsVPadConnected()
{
    VPADStatus dump;
    VPADReadError err;
    while (tp_true)
    {
        VPADRead(VPAD_CHAN_0, &dump, 1, &err);
        switch (err)
        {
        case VPAD_READ_SUCCESS:
        case VPAD_READ_NO_SAMPLES:
            return tp_true;
        case VPAD_READ_INVALID_CONTROLLER:
            return tp_false;
        case VPAD_READ_BUSY:
            TP_LogConstStr("UH OH");
            continue;
        case VPAD_READ_UNINITIALIZED:
            return tp_false;
        }
    }
}

static tp_bool IsVPadButtonPressed(const TP_Input_Button button)
{
    if (button == TP_Input_Button_MISC_TOUCH)
    {
        return currentVPadStatus.tpNormal.touched;
    }
    
    const VPADButtons vpadButton = TP_Input_ButtonToVPAD(button);
    return currentVPadStatus.hold & vpadButton;
}

static tp_bool IsVPadButtonSupported(const TP_Input_Button button)
{
    return TP_Input_ButtonToVPAD(button) != VPAD_BUTTON_NONE;
}

static float GetVPadAxisValue(const TP_Input_Axis axis)
{
    switch (axis)
    {
    case TP_Input_Axis_POINTER_X:
        return (float)(vpadXTouch) / 1920.0f;
    case TP_Input_Axis_POINTER_Y:
        return (float)(vpadYTouch) / 1080.0f;
    case TP_Input_Axis_PAD_STICK_LEFT_X:
        return currentVPadStatus.leftStick.x;
    case TP_Input_Axis_PAD_STICK_LEFT_Y:
        return currentVPadStatus.leftStick.y;
    case TP_Input_Axis_PAD_STICK_RIGHT_X:
        return currentVPadStatus.rightStick.x;
    case TP_Input_Axis_PAD_STICK_RIGHT_Y:
        return currentVPadStatus.rightStick.y;
    default: return 0;
    }
}

static tp_bool GetVPadAxisSupported(const TP_Input_Axis axis)
{
    switch (axis)
    {
    case TP_Input_Axis_POINTER_X:
    case TP_Input_Axis_POINTER_Y:
    case TP_Input_Axis_PAD_STICK_LEFT_X:
    case TP_Input_Axis_PAD_STICK_LEFT_Y:
    case TP_Input_Axis_PAD_STICK_RIGHT_X:
    case TP_Input_Axis_PAD_STICK_RIGHT_Y:
        return tp_true;
    default: return tp_false;
    }
}