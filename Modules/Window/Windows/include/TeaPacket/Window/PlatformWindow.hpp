#pragma once

#include <unordered_map>

#include <optional>
#include <windows.h>
#include "TeaPacket/Types/Numeric.h"

namespace TeaPacket::Window::Windows
{
    typedef std::optional<LRESULT> (CALLBACK* TPWndProc)(HWND, UINT, WPARAM, LPARAM);

}


struct TP_Window
{
    /// The Win32 HWND this Window uses.
    HWND windowHandle;

    tp_u16 x, y, w, h;

    /// A list of windowProcs that will be used.
    std::vector<TeaPacket::Window::Windows::TPWndProc> windowProcs;

    static inline bool shouldQuit = false;
};

TP_Window* TP_Window_Windows_GetWindowFromHWND(HWND hWnd);