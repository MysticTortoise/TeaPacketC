#pragma once

#include <windows.h>
#include "TeaPacket/Types/Numeric.h"

struct TP_Window
{
    /// The Win32 HWND this Window uses.
    HWND windowHandle;

    tp_u16 x, y, w, h;

    static inline bool shouldQuit = false;
};