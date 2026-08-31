#include <stdlib.h>

#include "TeaPacket/Bundled/Init.h"
#include "TeaPacket/Bundled/DeInit.h"

#include "TeaPacket/Graphics/GS/Display.h"

static const TP_GfxGS_DisplayParams dispParams = {
    1280,
    720,
};
static const TP_GfxGS_DisplayParamList dispParamList = {
    &dispParams,
    1
};


int main(void)
{
    if (!TP_Bundled_Init())
    {
        TP_Bundled_DeInit();
        return -1;
    }
    TP_Graphics_InitDefaultDisplays(dispParamList);

    while (TP_System_ShouldRun())
    {
        TP_System_Process();
        TP_Input_UpdateControllers();
        {
            TP_Input_Slot i;
            for (i = 0; i < TP_Input_GetSlotCount(); i++)
            {
                if (!TP_Input_IsConnected(i))
                    continue;
                TP_Input_PollSlot(i);
            }
        }

        {
            /* MOUSE TEST */
            const TP_Input_Slot mouseSlot = TP_Input_GetLastSlotPressed(TP_Input_ControllerType_Mouse);
            if (mouseSlot != TP_Input_NoControllerSlot)
            {
                TP_LogConstStr("MOUSE AT:");
                TP_LogDouble(TP_Input_GetAxis(mouseSlot, TP_Input_Axis_POINTER_X));
                TP_LogConstStr(",");
                TP_LogDouble(TP_Input_GetAxis(mouseSlot, TP_Input_Axis_POINTER_Y));

                TP_LogConstStr("IS CLICKED:");
                TP_LogBool(TP_Input_IsButtonPressed(mouseSlot, TP_Input_Button_MOUSE_LEFT));
            }
        }

        {
            /* KEYBOARD TEST */
            const TP_Input_Slot keyboardSlot = TP_Input_GetLastSlotPressed(TP_Input_ControllerType_Keyboard);
            if (keyboardSlot != TP_Input_NoControllerSlot)
            {
                TP_LogConstStr("IS ENTER PRESSED:");
                TP_LogBool(TP_Input_IsButtonPressed(keyboardSlot, TP_Input_Button_KEY_ENTER));
            }
        }

        {
            /* PAD TEST */
            const TP_Input_Slot padSlot = TP_Input_GetLastSlotPressed(TP_Input_ControllerType_Gamepad);
            if (padSlot != TP_Input_NoControllerSlot)
            {
                TP_LogConstStr("LSTICK:");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_PAD_STICK_LEFT_X));
                TP_LogConstStr(",");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_PAD_STICK_LEFT_Y));

                TP_LogConstStr("RSTICK:");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_PAD_STICK_RIGHT_X));
                TP_LogConstStr(",");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_PAD_STICK_RIGHT_Y));

                TP_LogConstStr("IS A PRESSED:");
                TP_LogBool(TP_Input_IsButtonPressed(padSlot, TP_Input_Button_PAD_A));
                TP_LogConstStr("IS B PRESSED:");
                TP_LogBool(TP_Input_IsButtonPressed(padSlot, TP_Input_Button_PAD_B));
            }
        }

        {
            /* WIIU TOUCH TEST */
            const TP_Input_Slot padSlot = TP_Input_GetLastSlotPressed(TP_Input_ControllerType_Gamepad);
            if (padSlot != TP_Input_NoControllerSlot)
            {
                TP_LogConstStr("TOUCH AT:");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_POINTER_X));
                TP_LogConstStr(",");
                TP_LogDouble(TP_Input_GetAxis(padSlot, TP_Input_Axis_POINTER_Y));

                TP_LogConstStr("IS CLICKED:");
                TP_LogBool(TP_Input_IsButtonPressed(padSlot, TP_Input_Button_MISC_TOUCH));
            }
        }

        system("cls");


    }


    TP_Bundled_DeInit();
    return 0;
}