#include "TeaPacket/Input/Input.h"

#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"

#include "TeaPacket/Input/GameInput/VirtualKey.gen"

#include <windowsx.h>

#include <unordered_set>

static struct
{
    float xPos{}, yPos{};

    bool leftMousePressed{};
    bool rightMousePressed{};
    bool middleMousePressed{};


    std::unordered_set<unsigned char> keysDown;
} InternalReading;
unsigned short keysDownPtr;

decltype(InternalReading) ExternalReading;

static void SetMousePosFromLParam(const HWND hWnd, const LPARAM lParam)
{
    RECT rect;
    GetClientRect(hWnd, &rect);

    InternalReading.xPos = static_cast<float>((GET_X_LPARAM(lParam) - rect.left)) / static_cast<float>(rect.right - rect.left);
    InternalReading.yPos = static_cast<float>((GET_Y_LPARAM(lParam) - rect.top)) / static_cast<float>(rect.bottom - rect.top);
}
static std::optional<LRESULT> WindowProc(const HWND hWnd, const UINT message, [[maybe_unused]] const WPARAM wParam, const LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
        SetCapture(hWnd);
        InternalReading.leftMousePressed = true;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_LBUTTONUP:
        ReleaseCapture();
        InternalReading.leftMousePressed = false;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_RBUTTONDOWN:
        SetCapture(hWnd);
        InternalReading.rightMousePressed = true;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_RBUTTONUP:
        ReleaseCapture();
        InternalReading.rightMousePressed = false;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_MBUTTONDOWN:
        SetCapture(hWnd);
        InternalReading.middleMousePressed = true;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_MBUTTONUP:
        ReleaseCapture();
        InternalReading.middleMousePressed = false;
        SetMousePosFromLParam(hWnd, lParam);
        return 0;
    case WM_MOUSEMOVE:
        SetMousePosFromLParam(hWnd, lParam);
        return 0;

    case WM_KEYDOWN:
        InternalReading.keysDown.emplace(static_cast<unsigned char>(wParam));
        return 0;
    case WM_KEYUP:
        InternalReading.keysDown.erase(static_cast<unsigned char>(wParam));
        return 0;
    default:
        return std::nullopt;
    }
}

static void UpdateInputHooks()
{
    for (size_t i = 0; i < TP_Window_GetCount(); i++)
    {
        TP_Window* window = TP_Window_Get(i);
        bool hasHook = false;

        for (const auto proc : window->windowProcs)
        {
            if (proc == WindowProc)
            {
                hasHook = true;
                break;
            }
        }
        if (!hasHook)
        {
            window->windowProcs.emplace_back(WindowProc);
        }
    }
}

tp_bool TP_Input_Init()
{
    UpdateInputHooks();

    return tp_true;
}

void TP_Input_DeInit()
{
    for (size_t i = 0; i < TP_Window_GetCount(); i++)
    {
        TP_Window* window = TP_Window_Get(i);

        for (const auto proc : window->windowProcs)
        {
            if (proc == WindowProc)
            {
                window->windowProcs.erase(std::next(window->windowProcs.begin()));
                break;
            }
        }
    }
}

void TP_Input_UpdateControllers()
{
    UpdateInputHooks();
}

void TP_Input_PollSlot(const TP_Input_Slot slot)
{
    if (slot == 0)
        ExternalReading = InternalReading;
}

tp_bool TP_Input_IsConnected(const TP_Input_Slot slot)
{
    return slot == 0;
}

tp_bool TP_Input_IsButtonPressed(TP_Input_Slot slot, TP_Input_Button button)
{
    if (slot != 0)
        return tp_false;

    if (button > TP_Input_Button_START_KEY && button < TP_Input_Button_END_KEY)
    {
        const unsigned char vk = TP_Input_ButtonToVK(button);
        return ExternalReading.keysDown.count(vk) != 0;
    }

    switch (button)
    {
    case TP_Input_Button_MOUSE_LEFT:
        return ExternalReading.leftMousePressed;
    case TP_Input_Button_MOUSE_RIGHT:
        return ExternalReading.rightMousePressed;
    case TP_Input_Button_MOUSE_MIDDLE:
        return ExternalReading.middleMousePressed;
    default:
        return tp_false;
    }
}

tp_bool TP_Input_IsButtonSupported(TP_Input_Slot slot, TP_Input_Button button)
{
    if (slot != 0)
        return tp_false;

    switch (button)
    {
    case TP_Input_Button_MOUSE_LEFT:
    case TP_Input_Button_MOUSE_RIGHT:
    case TP_Input_Button_MOUSE_MIDDLE:
        return tp_true;

    default:
        return tp_false;
    }
}

float TP_Input_GetAxis(TP_Input_Slot slot, TP_Input_Axis axis)
{
    if (slot != 0)
        return tp_false;

    switch (axis)
    {
    case TP_Input_Axis_POINTER_X:
        return ExternalReading.xPos;
    case TP_Input_Axis_POINTER_Y:
        return ExternalReading.yPos;

    default:
        return 0;
    }
}

tp_bool TP_Input_IsAxisSupported(TP_Input_Slot slot, TP_Input_Axis axis)
{
    if (slot != 0)
        return tp_false;

    switch (axis)
    {
    case TP_Input_Axis_POINTER_X:
    case TP_Input_Axis_POINTER_Y:
        return tp_true;

    default:
        return tp_false;
    }
}

constexpr static char ControllerName[] = "Mouse & Keyboard";
TP_String TP_Input_GetControllerName(const TP_Input_Slot slot)
{
    if (slot != 0)
        return {nullptr, 0};

    const TP_String str = {static_cast<char*>(TP_MemAlloc(sizeof(ControllerName))), sizeof(ControllerName)};
    std::memcpy(str.p, ControllerName, sizeof(ControllerName));
    return str;
}

TP_Input_Slot TP_Input_GetLastSlotPressed(TP_Input_ControllerType typeFilter)
{
    switch (typeFilter)
    {
    case TP_Input_ControllerType_Mouse:
    case TP_Input_ControllerType_Keyboard:
        return 0;
    default:
        return TP_Input_NoControllerSlot;
    }
}

TP_Input_Slot TP_Input_GetSlotCount()
{
    return 1;
}
