#pragma once
#include "TeaPacket/Graphics/MeshParams.h"

#include "TeaPacket/Types/SpanView.hpp"
#include "TeaPacket/Graphics/VariableType.hpp"

namespace TeaPacket::Graphics
{
    struct MeshParams
    {
        SpanView<unsigned char> vertexData;
        SpanView<VariableType> vertexInfo;
        SpanView<std::remove_reference_t<decltype(TP_Graphics_MeshIndexList::p[0])>> indexList;

        static_assert(std::is_same_v<
            SpanView<std::remove_const_t<std::remove_reference_t<decltype(TP_Graphics_MeshIndexList::p[0])>>>,
            SpanView<tp_u32>
            >);
    };
}
