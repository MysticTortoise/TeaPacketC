#include "TeaPacket/Input/Input.h"

#include <algorithm>
#include <cassert>
#include <GameInput.h>
#include <mutex>
#include <shared_mutex>
#include <vector>

#include "TeaPacket/MacroUtils/WindowsSpecific.hpp"

#include "TeaPacket/Input/GameInputGlobal.hpp"
#include "TeaPacket/Input/GameInput/VirtualKey.gen"
#include "TeaPacket/Input/GameInput/MouseButtons.gen"
#include "TeaPacket/Input/GameInput/ControllerType.gen"
#include "TeaPacket/Input/GameInput/GamepadButtons.gen"
#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"

using namespace TeaPacket;
using namespace TeaPacket::Input;

static GameInputCallbackToken globalCallbackToken;

struct ReadingEntry
{
    Microsoft::WRL::ComPtr<IGameInputReading> currentReading;
    Microsoft::WRL::ComPtr<IGameInputReading> lastReading;
};

static std::shared_mutex connectedDevices_m;
static std::vector<Microsoft::WRL::ComPtr<IGameInputDevice>> connectedDevices_v;
static std::shared_mutex publicDevices_m;
static decltype(connectedDevices_v) publicDevices_v;
static std::shared_mutex readings_m;
static std::vector<ReadingEntry> readings_v;

void CALLBACK OnDeviceEnumerated(
    [[maybe_unused]] _In_ GameInputCallbackToken callbackToken,
    [[maybe_unused]] _In_ void * context,
    [[maybe_unused]] _In_ IGameInputDevice * device,
    [[maybe_unused]] _In_ uint64_t timestamp,
    [[maybe_unused]] _In_ const GameInputDeviceStatus currentStatus,
    [[maybe_unused]] _In_ GameInputDeviceStatus previousStatus)
{
    std::unique_lock lock(connectedDevices_m);
    if (currentStatus & GameInputDeviceConnected)
    {
        // Connected
        for (auto& i : connectedDevices_v)
        {
            if (i == nullptr)
            {
                i = device;
                return;
            }
        }
        connectedDevices_v.emplace_back(device);
    } else
    {
        // Disconnected
        for (auto& i : connectedDevices_v)
        {
            if (i.Get() == device)
            {
                i = nullptr;
                return;
            }
        }
    }
}

void TP_Input_UpdateControllers()
{
    std::unique_lock ulock(publicDevices_m, std::defer_lock);
    std::unique_lock ulock2(readings_m, std::defer_lock);
    std::shared_lock slock(connectedDevices_m, std::defer_lock);
    std::lock(ulock, ulock2, slock);

    publicDevices_v = connectedDevices_v;
    readings_v.resize(publicDevices_v.size());
}

tp_bool TP_Input_IsConnected(TP_Input_Slot slot)
{
    std::shared_lock lock(connectedDevices_m);
    return connectedDevices_v[slot] != nullptr;
}

void TP_Input_PollSlot(TP_Input_Slot slot)
{
    std::shared_lock slock(publicDevices_m, std::defer_lock);
    std::unique_lock ulock(readings_m, std::defer_lock);
    std::lock(slock, ulock);
    // ReSharper disable once CppUseStructuredBinding
    auto& reading = readings_v[slot];
    reading.lastReading = reading.currentReading;
    
    if (!SUCCEEDED(gameInput->GetCurrentReading(
        GameInputKindAny,
        publicDevices_v[slot].Get(),
        reading.currentReading.GetAddressOf()
        )))
    {
        reading.currentReading = nullptr;
        return;
    }
}

tp_bool TP_Input_Init()
{
    CheckErrorWinCom(
        GameInputCreate(gameInput.GetAddressOf())
    );

    CheckErrorWinCom(
        gameInput->RegisterDeviceCallback(
            nullptr,
            GameInputKindAny,
            GameInputDeviceConnected,
            GameInputAsyncEnumeration,
            nullptr,
            OnDeviceEnumerated,
            &globalCallbackToken)
    );
    return tp_true;
}

TP_Input_Slot TP_Input_GetSlotCount()
{
    std::shared_lock lock(publicDevices_m);
    return static_cast<TP_Input_Slot>(publicDevices_v.size());
}

tp_bool TP_Input_IsButtonPressed(TP_Input_Slot slot, TP_Input_Button button)
{
    std::shared_lock lock(readings_m);
    IGameInputReading* reading = readings_v[slot].currentReading.Get();
    
    if (button > TP_Input_Button_START_KEY && button < TP_Input_Button_END_KEY)
    {
        const uint8_t virtualKey = TP_Input_ButtonToVK(button);
        const uint32_t keyCount = reading->GetKeyCount();
        auto keys = std::vector<GameInputKeyState>(keyCount);
        reading->GetKeyState(keyCount, keys.data());
        
        for (uint32_t i = 0; i < keyCount; i++)
        {
            if (keys[i].virtualKey == virtualKey)
            {
                return true;
            }
        }
        return false;
    }
    if (button > TP_Input_Button_START_MOUSE && button < TP_Input_Button_END_MOUSE)
    {
        GameInputMouseState mouseState{};
        reading->GetMouseState(&mouseState);
        return mouseState.buttons & TP_Input_ButtonToMouseButton(button);
    }
    if (button > TP_Input_Button_START_PAD && button < TP_Input_Button_END_PAD)
    {
        GameInputGamepadState gamepadState{};
        reading->GetGamepadState(&gamepadState);
        return gamepadState.buttons & TP_Input_ButtonToGamepadButton(button);
    }

    return false;
}

static void TP_GetWindowRect(RECT* rect)
{
    assert(rect != nullptr);
    assert(TP_Window_Get(0) != nullptr);
    GetWindowRect(TP_Window_Get(0)->windowHandle, rect);
}

float TP_Input_GetAxis(TP_Input_Slot slot, TP_Input_Axis axis)
{
    std::shared_lock lock(readings_m, std::defer_lock);
    std::shared_lock lock2(publicDevices_m, std::defer_lock);
    std::lock(lock, lock2);
    
    if (axis == TP_Input_Axis_POINTER_X || axis == TP_Input_Axis_POINTER_Y)
    {
        const GameInputDeviceInfo* info;
        if (!SUCCEEDED(publicDevices_v[slot]->GetDeviceInfo(&info)))
        {
            return 0;
        }
        if (info->supportedInput & GameInputKindMouse)
        {
            // POINTER is a mouse
            RECT windowRect;
            TP_GetWindowRect(&windowRect);
            GameInputMouseState mouseState{};
            readings_v[slot].currentReading->GetMouseState(&mouseState);
            
            if (axis == TP_Input_Axis_POINTER_X)
            {
                return  std::clamp(
                    static_cast<float>(mouseState.absolutePositionX - windowRect.left) /
                        static_cast<float>(windowRect.right - windowRect.left),
                        0.0f, 1.0f);
            } else
            {
                return  std::clamp(static_cast<float>(mouseState.absolutePositionY - windowRect.top) /
                        static_cast<float>(windowRect.bottom - windowRect.top),
                        0.0f, 1.0f);
            }
        }
        return 0;
    }
    if (axis > TP_Input_Axis_START_PAD && axis < TP_Input_Axis_END_PAD)
    {
        GameInputGamepadState state = {};
        readings_v[slot].currentReading->GetGamepadState(&state);
        switch (axis)
        {
        case TP_Input_Axis_PAD_STICK_LEFT_X:
            return state.leftThumbstickX;
        case TP_Input_Axis_PAD_STICK_LEFT_Y:
            return state.leftThumbstickY;
        case TP_Input_Axis_PAD_STICK_RIGHT_X:
            return state.rightThumbstickX;
        case TP_Input_Axis_PAD_STICK_RIGHT_Y:
            return state.rightThumbstickY;
        default:
            return 0;
        }
    }

    return 0;
}


tp_bool TP_Input_IsButtonSupported(TP_Input_Slot slot, TP_Input_Button button)
{
    std::shared_lock lock(publicDevices_m);
    const GameInputDeviceInfo* info;
    const auto device = publicDevices_v[slot].Get();
    if (!SUCCEEDED(device->GetDeviceInfo(&info)))
    {
        return false;
    }
    if (button > TP_Input_Button_START_KEY && button < TP_Input_Button_END_KEY)
    {
        return info->supportedInput & GameInputKindKeyboard; // TODO: Is there a way to figure this out on a more granular level?
    } else if (button > TP_Input_Button_START_MOUSE && button < TP_Input_Button_END_MOUSE)
    {
        if (!(info->supportedInput & GameInputKindMouse))
        {
            return false;
        }
        return info->mouseInfo->supportedButtons & TP_Input_ButtonToMouseButton(button);
    }

    return false;
}

tp_bool TP_Input_IsAxisSupported(TP_Input_Slot slot, TP_Input_Axis axis)
{
    std::shared_lock lock(publicDevices_m);
    const GameInputDeviceInfo* info;
    const auto device = publicDevices_v[slot].Get();
    if (!SUCCEEDED(device->GetDeviceInfo(&info)))
    {
        return false;
    }
    if (axis == TP_Input_Axis_POINTER_X || axis == TP_Input_Axis_POINTER_Y)
    {
        return info->supportedInput & GameInputKindMouse;
    }
    return false;
}


TP_Input_Slot TP_Input_GetLastSlotPressed(TP_Input_ControllerType typeFilter)
{
    Microsoft::WRL::ComPtr<IGameInputReading> reading;
    if (!SUCCEEDED(gameInput->GetCurrentReading(
        TP_Input_ControllerTypeToGameInputKind(typeFilter),
        nullptr,
        reading.GetAddressOf())))
    {
        return NoControllerSlot;
    }
    IGameInputDevice* device;
    reading->GetDevice(&device);
    
    std::shared_lock lock(publicDevices_m);
    for (size_t slot = 0; slot < publicDevices_v.size(); ++slot)
    {
        if (publicDevices_v[slot].Get() == device)
        {
            return static_cast<TP_Input_Slot>(slot);
        }
    }
    return NoControllerSlot;
}

TP_String TP_Input_GetControllerName(TP_Input_Slot slot)
{
    const GameInputDeviceInfo* info;
    std::shared_lock lock(publicDevices_m);
    if (!SUCCEEDED(publicDevices_v[slot]->GetDeviceInfo(&info)))
    {
        const TP_String str = {static_cast<char*>(calloc(1, 1)), 1};
        return str;
    }
    const size_t length = std::min(strlen(info->displayName),static_cast<size_t>(100));

    const TP_String str = {static_cast<char*>(malloc(length)), length};
    memcpy(str.p, info->displayName, length);
    return str;
}


void TP_Input_DeInit()
{
    gameInput->UnregisterCallback(globalCallbackToken);
    //gameInput->Release();
}