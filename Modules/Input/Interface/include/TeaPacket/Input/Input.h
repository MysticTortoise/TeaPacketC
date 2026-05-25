
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
const TP_Input_Slot TP_Input_NoControllerSlot = UINT_MAX;

tp_bool TP_Input_Init(void);
void TP_Input_DeInit(void);

/**
 * Updates the status of all controllers. This does NOT poll input, but it does update all other data.
 */
void TP_Input_UpdateControllers(void);

/**
 * Polls all input for a controller. Controller input data will not update unless this function is called.
 * @param slot The controller slot to poll.
 */
void    TP_Input_PollSlot(TP_Input_Slot slot);

/**
 * Checks whether a slot has a connected controller or not.
 * @param slot The slot to check.
 * @return Whether the given slot has a controller connected.
 */
tp_bool TP_Input_IsConnected(       TP_Input_Slot slot);
/**
 * Checks whether a slot has a button pressed or not.
 * @param slot The slot to check.
 * @param button The button to check.
 * @return Whether the given slot has the given button currently pressed down.
 */
tp_bool TP_Input_IsButtonPressed(   TP_Input_Slot slot, TP_Input_Button button);
/**
 * Gets the value of an axis from a controller.
 * @param slot The slot to check.
 * @param axis The axis to read.
 * @return The value of the given axis on the controller, or 0 if the axis is not supported.
 */
float   TP_Input_GetAxis(           TP_Input_Slot slot, TP_Input_Axis axis);

/**
 * Checks if a controller supports a button.
 * @param slot The slot to check
 * @param button The button to check.
 * @return Whether the controller connected in the given slot supports the given button or not.
 */
tp_bool TP_Input_IsButtonSupported( TP_Input_Slot slot, TP_Input_Button button);
/**
 * Checks if a controller supports an axis.
 * @param slot The slot to check
 * @param axis The axis to check.
 * @return Whether the controller connected in the given slot supports the given axis or not.
 */
tp_bool TP_Input_IsAxisSupported(   TP_Input_Slot slot, TP_Input_Axis axis);

/**
 * Gets the name of a controller connected to a given slot.
 * @param slot The slot to check.
 * @return The name of the controller connected to that slot.
 */
TP_String TP_Input_GetControllerName(TP_Input_Slot slot);

/**
 * Gets the last controller that has pressed a button.
 * @param typeFilter Filters out any controllers that do not match this type.
 * @return The last controller, after filtering, that has pressed a button.
 */
TP_Input_Slot TP_Input_GetLastSlotPressed(TP_Input_ControllerType typeFilter);
/**
 * Gets the current slot count.
 *
 * @details On platforms that support a fixed number of controllers, this function will return that number.
 * On platforms that support a variable number of controllers (i.e. desktops, mobile, etc.) this function will return the current highest slot connected + 1.
 * @return The current slot count.
 */
TP_Input_Slot TP_Input_GetSlotCount(void);


#ifdef __cplusplus
}
#endif
#endif
