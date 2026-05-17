#pragma once

#include "TeaPacket/Window/WindowParams.h"

#include <string_view>

namespace TeaPacket::Window
{
    struct WindowParams
    {
        tp_u16 x, y, width, height;

        std::string_view title;
    };

    static_assert(
        sizeof(WindowParams) - sizeof(WindowParams::title) == // NOLINT(*-sizeof-container)
        sizeof(TP_Window_Params) - sizeof(TP_Window_Params::title)
        );
}