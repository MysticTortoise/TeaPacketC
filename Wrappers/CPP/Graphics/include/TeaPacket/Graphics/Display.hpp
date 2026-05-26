#pragma once
#include "TeaPacket/Graphics/Display.h"

#include "TeaPacket/Graphics/DisplayParams.hpp"
#include "TeaPacket/Types/SpanView.hpp"
#include "TeaPacket/Types/TPArray.hpp"

namespace TeaPacket::Graphics
{
    typedef TP_Graphics_DisplayID DisplayID;

    class Display
    {
    public:
        DisplayID id;

        explicit Display(const DisplayID id):id(id)
        {

        }

        static void InitDefaultDisplays(SpanView<DisplayParams> params)
        {
            TP_Graphics_InitDefaultDisplays(SpanToTPArrayCast(params, TP_Graphics_DisplayParams));
        }

        static DisplayID GetCount()
        {
            return TP_Graphics_Display_GetCount();
        }

        void BeginRender() const
        {
            TP_Graphics_Display_BeginRender(id);
        }

        static void BeginRender(const DisplayID id)
        {
            TP_Graphics_Display_BeginRender(id);
        }

        static void FinishRender()
        {
            TP_Graphics_Display_FinishRender();
        }

        [[nodiscard]] tp_u16 GetWidth() const
        {
            return TP_Graphics_Display_GetWidth(id);
        }

        [[nodiscard]] tp_u16 GetHeight() const
        {
            return TP_Graphics_Display_GetHeight(id);
        }

        static void PresentAll(const bool waitForVSync)
        {
            TP_Graphics_Display_PresentAll(waitForVSync);
        }
    };
}
