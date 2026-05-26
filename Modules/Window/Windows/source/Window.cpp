/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Window/PlatformWindow.hpp"

#include "TeaPacket/Memory/Memory.h"

#include <atomic>
#include <memory>
#include <vector>


static LRESULT WindowProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
    const auto ptr = reinterpret_cast<TP_Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    if (ptr != nullptr)
    {
        for (const auto func : ptr->windowProcs)
        {
            const std::optional<LRESULT> result = func(hWnd, message, wParam, lParam);
            if (result.has_value())
                return result.value();
        }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

static std::optional<LRESULT> WindowProcQuit([[maybe_unused]] const HWND hWnd, const UINT message,
                                             [[maybe_unused]] const WPARAM wParam,
                                             [[maybe_unused]] const LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    case WM_QUIT:
        PostQuitMessage(0);
        // TODO: multiple windows on closing can be closed individually
        TP_Window::shouldQuit = true;
        return 0;
    default: return std::nullopt;
    }
}

static std::atomic_bool IsWindowClassInitialized(false);

static void InitializeWindowClass()
{
    IsWindowClassInitialized.store(true);

    WNDCLASS windowClass;
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandle(nullptr);
    windowClass.hIcon = nullptr;
    windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    windowClass.hbrBackground = CreateSolidBrush(RGB(29, 29, 38));
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = "TeaPacket_MainWindowClass";

    if (!RegisterClass(&windowClass))
    {
        // Fatal Error
    }
}

static inline auto Windows = std::vector<TP_Window*>();

TP_Window* TP_Window_Create(const TP_Window_Params* params)
{
    if (!IsWindowClassInitialized.load()) { InitializeWindowClass(); }
    const size_t nameSize = params->title.size;
    const auto titleName = new char[nameSize + 1];
    memcpy(titleName, params->title.p, nameSize);
    titleName[nameSize] = '\0';

    HWND winHandle = CreateWindowExA(
        0,
        "TeaPacket_MainWindowClass",
        titleName,
        WS_OVERLAPPEDWINDOW,
        params->x, params->y,
        params->width, params->height,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );

    if (winHandle == nullptr)
    {
        // Error handling
    }
    auto* window = new TP_Window{
        winHandle,
        params->x,
        params->y,
        params->width,
        params->height
    };
    SetWindowLongPtr(winHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    window->windowProcs.emplace_back(WindowProcQuit);
    ShowWindow(winHandle, SW_SHOWNORMAL);

    Windows.emplace_back(window);


    delete[] titleName;
    return window;
}

static thread_local MSG msg;

void TP_Window_ProcessEvents(TP_Window* window)
{
    const HWND hwnd = window->windowHandle;
    while (PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

void TP_Window_Destroy(TP_Window* window)
{
    for (size_t i = 0; i < Windows.size(); i++)
    {
        if (Windows[i] == window)
        {
            Windows.erase(Windows.begin() + i);
            break;
        }
    }
    DestroyWindow(window->windowHandle);

    delete window;
}

tp_u16 TP_Window_GetXPos(TP_Window* window)
{
    return window->x;
}

tp_u16 TP_Window_GetYPos(TP_Window* window)
{
    return window->y;
}

tp_u16 TP_Window_GetWidth(TP_Window* window)
{
    return window->w;
}

tp_u16 TP_Window_GetHeight(TP_Window* window)
{
    return window->h;
}

TP_String TP_Window_GetTitle(TP_Window* window)
{
    const int len = GetWindowTextLengthA(window->windowHandle);

    // ReSharper disable once CppDFAMemoryLeak
    const auto text = static_cast<char*>(TP_MemAlloc(len));
    GetWindowTextA(window->windowHandle, text, len);

    return {text, static_cast<size_t>(len)};
}

void TP_Window_SetXPos(TP_Window* window, const tp_u16 xPos)
{
    window->x = xPos;
    SetWindowPos(
        window->windowHandle,
        nullptr,
        xPos, window->y,
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void TP_Window_SetYPos(TP_Window* window, const tp_u16 yPos)
{
    window->y = yPos;
    SetWindowPos(
        window->windowHandle,
        nullptr,
        window->x, yPos,
        0, 0,
        SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void TP_Window_SetWidth(TP_Window* window, const tp_u16 width)
{
    window->w = width;
    SetWindowPos(
        window->windowHandle,
        nullptr,
        0, 0,
        width, window->h,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void TP_Window_SetHeight(TP_Window* window, const tp_u16 height)
{
    window->h = height;
    SetWindowPos(
        window->windowHandle,
        nullptr,
        0, 0,
        window->w, height,
        SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

void TP_Window_SetTitle(TP_Window* window, const TP_StringView name)
{
    const auto text = new char[name.size + 1];
    memcpy(text, name.p, name.size);
    text[name.size] = '\0';

    SetWindowTextA(window->windowHandle, text);

    delete[] text;
}

size_t TP_Window_GetCount()
{
    return Windows.size();
}

TP_Window* TP_Window_Get(const size_t index)
{
    return Windows.at(index);
}

tp_u16 TP_Window_GetID(const TP_Window* window)
{
    for (size_t i = 0; i < Windows.size(); ++i)
    {
        if (window == Windows.at(i))
            return static_cast<tp_u16>(i);
    }
    return TP_MAXU16;
}
