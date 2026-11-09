#include "TeaPacket/Input/Input.h"

#import <GameController/GameController.h>

#include "TeaPacket/Input/GameController/GCKeyCode.gen"

#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Time/Time.h"
#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Window/PlatformWindow.h"

static __unsafe_unretained NSMutableArray<id>* listenerArray = nil;
static __unsafe_unretained NSMutableArray* deviceArray = nil;
static __unsafe_unretained NSMutableArray<id>* polledInputArray = nil;

struct __attribute__((objc_boxable)) ControllerCurrentState
{
    id controller;
    tp_timeunit timestamp;
};

static __unsafe_unretained NSMutableDictionary* activeControllerDictionary;

static void AddDevice(id<GCDevice> device)
{
    (void)device;

    size_t assignedID = SIZE_MAX;
    for(size_t i = 0; i < [deviceArray count]; i++)
    {
        if([[deviceArray objectAtIndex:i] isKindOfClass:[NSNull class]])
        {
            assignedID = i;
            deviceArray[i] = device;
            break;
        }
    }
    if(assignedID == SIZE_MAX)
    {
        assignedID = [deviceArray count];
        [deviceArray addObject:device];
    }

    NSLog(@"connected %@ in slot %zu",[device vendorName], assignedID);
}

static void RemoveDevice(id<GCDevice> device)
{
    size_t assignedID = UINT_MAX;
    for(size_t i = 0; i < [deviceArray count]; i++)
    {
        if([deviceArray objectAtIndex:i] == device)
        {
            assignedID = i;
            [deviceArray replaceObjectAtIndex: i withObject:[NSNull null]];
            break;
        }
    }
    NSLog(@"disconnected %@ from slot %zu",[device vendorName], assignedID);
}

static void MakeDeviceCurrent(id<GCDevice> device, id type)
{
    struct ControllerCurrentState currentState;
    currentState.controller = device;
    currentState.timestamp = TP_Time_GetMicroseconds();

    activeControllerDictionary[type] = @(currentState);
}

static id GetItemFromArrayDyn(NSMutableArray* array, size_t i)
{
    if([array count] <= i)
    {
        return nil;
    }
    id obj = [array objectAtIndex:i];
    if([obj isKindOfClass:[NSNull class]])
    {
        return nil;
    }
    return obj;
}

static id<GCDevice> GetDeviceFromID(TP_Input_Slot slot)
{
    return GetItemFromArrayDyn(deviceArray, slot);
}

static id GetPolledInputFromID(TP_Input_Slot slot)
{
    return GetItemFromArrayDyn(polledInputArray, slot);
}

static id GetClassFromControllerType(const TP_Input_ControllerType type)
{
    switch(type)
    {
        case TP_Input_ControllerType_Keyboard: return [GCKeyboard class];
        case TP_Input_ControllerType_Mouse: return [GCMouse class];
        case TP_Input_ControllerType_Gamepad: return [GCController class];
        default: return nil;
    }
}

tp_bool TP_Input_Init(void)
{
    NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
    listenerArray = [NSMutableArray array];
    deviceArray = [NSMutableArray array];
    polledInputArray = [NSMutableArray array];
    activeControllerDictionary = [NSMutableDictionary dictionary];

    #define GCAddDeviceType(type) \
    [ listenerArray addObject:[center addObserverForName: type##DidConnectNotification \
            object: nil \
            queue: nil \
            usingBlock: ^(NSNotification* note) {AddDevice(note.object);} \
    ]]; \
    [ listenerArray addObject:[center addObserverForName: type##DidDisconnectNotification \
            object: nil \
            queue: nil \
            usingBlock: ^(NSNotification* note) {RemoveDevice(note.object);} \
    ]]

    #define GCAddDeviceTypeWithCurrent(type) \
        GCAddDeviceType(type); \
    [ listenerArray addObject:[center addObserverForName: type##DidBecomeCurrentNotification \
        object: nil \
        queue: nil \
        usingBlock: ^(NSNotification* note) {MakeDeviceCurrent(note.object, [type class]);} \
    ]]



    GCAddDeviceTypeWithCurrent(GCController);
    GCAddDeviceType(GCKeyboard);
    GCAddDeviceTypeWithCurrent(GCMouse);



    #undef GCAddDeviceType
    #undef GCAddDeviceTypeWithCurrent
    return tp_true;
}

void TP_Input_DeInit(void)
{
    if(listenerArray)
    {
        NSNotificationCenter* center = [NSNotificationCenter defaultCenter];
        for(id listener in listenerArray)
        {
            [center removeObserver:listener];
        }

        [listenerArray release];
        listenerArray = nil;
    }

    if(deviceArray)
    {
        for(size_t i = 0; i < [deviceArray count]; i++)
        {
            if(![[deviceArray objectAtIndex:i] isKindOfClass:[NSNull class]])
            {
                RemoveDevice([deviceArray objectAtIndex:i]);
            }
        }

        [deviceArray release];
        deviceArray = nil;
    }

    if(activeControllerDictionary)
    {
        [activeControllerDictionary release];
        activeControllerDictionary = nil;
    }
}

void TP_Input_UpdateControllers(void)
{
    // Does nothing. Controllers are updated asynchronously (or is it not a problem cause of synchronous msg processing?).
    // This could be changed, but I can't be bothered, yet.
}

void TP_Input_PollSlot(TP_Input_Slot slot)
{
    id<GCDevice> device = GetDeviceFromID(slot);
    if(device == nil)
    {
        return;
    }
    if([polledInputArray count] <= slot)
    {
        for(unsigned int i = [polledInputArray count]; i <= slot; i++)
        {
            [polledInputArray addObject:[NSNull null]];
        }
    }

    if([device isKindOfClass:[GCKeyboard class]])
    {
        GCKeyboard* keyboard = device;
        id keyboardInput = [[keyboard keyboardInput] capture];
        [polledInputArray
            replaceObjectAtIndex:slot
            withObject: keyboardInput
        ];
        return;
    }
    if([device isKindOfClass:[GCMouse class]])
    {
        GCMouse* mouse = device;
        id mouseInput = [[mouse mouseInput] capture];
        [polledInputArray
            replaceObjectAtIndex:slot
            withObject: mouseInput
        ];
        return;
    }
    NSLog(@"Unknown controller %@ in slot %u", NSStringFromClass([device class]), slot);
    // TODO: Controller
}

tp_bool TP_Input_IsConnected(TP_Input_Slot slot)
{
    return GetDeviceFromID(slot) != nil;
}

tp_bool TP_Input_IsButtonPressed(TP_Input_Slot slot, TP_Input_Button button)
{
    id polled = GetPolledInputFromID(slot);
    if(polled == nil)
    {
        return tp_false;
    }


    if([polled isKindOfClass:[GCMouseInput class]])
    {
        if(button <= TP_Input_Button_START_MOUSE || slot >= TP_Input_Button_END_MOUSE)
        {
            return tp_false;
        }
        // Mouse
        GCMouseInput* mouseInput = polled;
        switch(button)
        {
            case TP_Input_Button_MOUSE_LEFT:
                return [[mouseInput leftButton] isPressed];
            case TP_Input_Button_MOUSE_RIGHT:
                return [[mouseInput rightButton] isPressed];
            case TP_Input_Button_MOUSE_MIDDLE:
                return [[mouseInput middleButton] isPressed];
            default:
                return tp_false;
        }
    }

    if([polled isKindOfClass:[GCKeyboardInput class]])
    {
        if(button <= TP_Input_Button_START_KEY || button >= TP_Input_Button_END_KEY)
        {
            return tp_false;
        }

        const GCKeyCode code = TP_Input_ButtonToGCKey(button);
        GCKeyboardInput* keyboardInput = polled;

        return [[keyboardInput buttonForKeyCode:code] isPressed];
    }
    // TODO: Controller input

    return tp_false;
}

static NSPoint GetMousePos(void)
{
    TP_Window* win = TP_Window_GetActive();
    NSWindow* window = win->window;

    return [window mouseLocationOutsideOfEventStream];
}

float TP_Input_GetAxis(TP_Input_Slot slot, TP_Input_Axis axis)
{
    id polled = GetPolledInputFromID(slot);
    if(polled == nil)
    {
        return tp_false;
    }


    if([polled isKindOfClass:[GCMouseInput class]])
    {
        // Mouse
        switch(axis)
        {
            case TP_Input_Axis_POINTER_X:
                return (float)GetMousePos().x;
            case TP_Input_Axis_POINTER_Y:
                return (float)GetMousePos().y;
            default:
                return 0;
        }
    }
    // TODO: Controller input

    return tp_false;
}

tp_bool TP_Input_IsButtonSupported(TP_Input_Slot slot, TP_Input_Button button)
{
    id polled = GetPolledInputFromID(slot);
    if(polled == nil)
    {
        return tp_false;
    }

    if([polled isKindOfClass:[GCMouseInput class]])
    {
        if(button <= TP_Input_Button_START_MOUSE || slot >= TP_Input_Button_END_MOUSE)
        {
            return tp_false;
        }
        // Mouse
        //GCMouseInput* mouseInput = polled;
        switch(button)
        {
            case TP_Input_Button_MOUSE_LEFT:
            case TP_Input_Button_MOUSE_RIGHT:
            case TP_Input_Button_MOUSE_MIDDLE:
                return tp_true;
            default:
                return tp_false;
        }
    }

    if([polled isKindOfClass:[GCKeyboardInput class]])
    {
        if(button <= TP_Input_Button_START_KEY || button >= TP_Input_Button_END_KEY || !TP_Input_ButtonConvertableToGCKey(button))
        {
            return tp_false;
        }

        const GCKeyCode code = TP_Input_ButtonToGCKey(button);
        GCKeyboardInput* keyboardInput = polled;
        GCControllerButtonInput* input = [keyboardInput buttonForKeyCode:code];

        return input != nil;
    }

    return tp_false;
}

tp_bool TP_Input_IsAxisSupported(TP_Input_Slot slot, TP_Input_Axis axis)
{
    id polled = GetPolledInputFromID(slot);
    if(polled == nil)
    {
        return tp_false;
    }

    if([polled isKindOfClass:[GCMouseInput class]])
    {
        switch(axis)
        {
            case TP_Input_Axis_POINTER_X:
            case TP_Input_Axis_POINTER_Y:
                return tp_true;
            default:
                return tp_false;
        }
    }

    return tp_false;
}

TP_String TP_Input_GetControllerName(TP_Input_Slot slot)
{
    (void)slot;
    TP_String str;

    id<GCDevice> controller = GetDeviceFromID(slot);
    if(controller == nil)
    {
        return (TP_String){0};
    }

    NSString* name = [controller vendorName];
    NSUInteger size;

    const NSStringEncoding encoding = NSUTF8StringEncoding;

    [name getBytes:NULL
        maxLength:0
        usedLength:&size
        encoding:encoding
        options:0
        range:NSMakeRange(0, [name length])
        remainingRange:NULL
        ];
    str.p = TP_MemAlloc(size);
    str.size = size;

    [name getBytes:str.p
        maxLength:str.size
        usedLength:&size
        encoding:encoding
        options:0
        range:NSMakeRange(0, [name length])
        remainingRange:NULL
        ];


    return str;
}

TP_Input_Slot TP_Input_GetLastSlotPressed(TP_Input_ControllerType typeFilter)
{
    id last = nil;
    if(typeFilter == TP_Input_ControllerType_Keyboard)
    {
        last = [GCKeyboard coalescedKeyboard];
    } else if(typeFilter != TP_Input_ControllerType_Any)
    {
        id type = GetClassFromControllerType(typeFilter);
        if(type == nil)
        {
            return TP_Input_NoControllerSlot;
        }
        id stateObj = activeControllerDictionary[type];
        if(stateObj == nil)
        {
            return TP_Input_NoControllerSlot;
        }

        struct ControllerCurrentState state;
        [stateObj getValue:&state];


        last = state.controller;

    } else
    {
        tp_timeunit latest = 0;
        for(id key in activeControllerDictionary)
        {
            NSValue* val = activeControllerDictionary[key];
            if(val == nil)
            {
                return TP_Input_NoControllerSlot;
            }

            struct ControllerCurrentState state;
            [val getValue:&state];

            if(state.timestamp > latest)
            {
                last = state.controller;
                latest = state.timestamp;
            }
        }
    }


    if(last == nil)
    {
        return TP_Input_NoControllerSlot;
    }

    return (TP_Input_Slot)[deviceArray indexOfObject:last];
}

TP_Input_Slot TP_Input_GetSlotCount(void)
{
    return [deviceArray count];
}