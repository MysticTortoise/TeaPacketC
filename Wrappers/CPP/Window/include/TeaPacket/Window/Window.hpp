// ReSharper disable CppMemberFunctionMayBeConst
#pragma once
#include "TeaPacket/Types/ClassDef.hpp"
#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Window/WindowParams.hpp"

#include "TeaPacket/Types/String.hpp"
#include "TeaPacket/Types/StringView.hpp"

namespace TeaPacket::Window
{
    class Window
    {
    public:
        TP_ClassWrapperDefP(Window, TP, TP_Window_Params)

        explicit Window(const WindowParams& params):
        Window(TP_Window_Params{
                .x = params.x,
                .y = params.y,
                .width = params.width,
                .height = params.height,
                .title = Types::StringViewToTP(params.title)
            })
        {}

        void ProcessEvents() const
        {
            TP_Window_ProcessEvents(p);
        }

        [[nodiscard]] auto GetXPos() const
        { return TP_Window_GetXPos(p); }

        [[nodiscard]] auto GetYPos() const
        { return TP_Window_GetYPos(p); }

        [[nodiscard]] auto GetWidth() const
        { return TP_Window_GetWidth(p); }

        [[nodiscard]] auto GetHeight() const
        { return TP_Window_GetHeight(p); }

        [[nodiscard]] TPString GetTitle() const
        {
            return TPString(TP_Window_GetTitle(p));
        }

        void SetXPos(const tp_u16 newX) const
        { TP_Window_SetXPos(p, newX); }

        void SetYPos(const tp_u16 newY) const
        { TP_Window_SetYPos(p, newY); }

        void SetWidth(const tp_u16 newWidth) const
        { TP_Window_SetWidth(p, newWidth); }

        void SetHeight(const tp_u16 newHeight) const
        { TP_Window_SetHeight(p, newHeight); }

        void SetTitle(const std::string_view newTitle) const
        {
            TP_Window_SetTitle(p, Types::StringViewToTP(newTitle));
        }






    };
}