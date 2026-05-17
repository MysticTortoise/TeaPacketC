#pragma once
#include "TeaPacket/Graphics/Graphics.h"

namespace TeaPacket::Graphics
{
    inline bool Init()
    {
        return TP_Graphics_Init();
    }

    inline void DeInit()
    {
        return TP_Graphics_DeInit();
    }

    inline void DrawMesh()
    {
        TP_Graphics_DrawMesh();
    }

    inline void ClearColor(const tp_u8 r, const tp_u8 g, const tp_u8 b)
    {
        TP_Graphics_ClearColor(r,g,b);
    }

    inline void SetDepthEnabled(const bool depthEnabled)
    {
        TP_Graphics_SetDepthEnabled(depthEnabled);
    }
}