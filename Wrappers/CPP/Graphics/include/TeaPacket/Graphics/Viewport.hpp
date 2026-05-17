#pragma once
#include "TeaPacket/Graphics/Viewport.h"

#include "TeaPacket/Graphics/ViewportParams.hpp"
#include "TeaPacket/Types/ClassDef.hpp"

namespace TeaPacket::Graphics
{
    class Viewport
    {
        TP_ClassWrapperDef(Viewport, TP_Graphics)

        explicit Viewport(const ViewportParams& params):
        Viewport(TP_Graphics_ViewportParams{
            .width = params.width,
            .height = params.height,
            .shaderUsable = params.shaderUsable
        })
        {}

        void BeginRender() const
        {
            TP_Graphics_Viewport_BeginRender(p);
        }

        void FinishRender() const
        {
            TP_Graphics_Viewport_FinishRender(p);
        }

        [[nodiscard]] tp_u16 GetWidth() const
        {
            return TP_Graphics_Viewport_GetWidth(p);
        }

        [[nodiscard]] tp_u16 GetHeight() const
        {
            return TP_Graphics_Viewport_GetHeight(p);
        }
    };
}
