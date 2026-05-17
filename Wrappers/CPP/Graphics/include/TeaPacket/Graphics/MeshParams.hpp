#pragma once
#include "../../../../../../Modules/Graphics/Interface/include/TeaPacket/Graphics/MeshParams.h"

#include <span>

#include "TeaPacket/Graphics/VariableType.hpp"

namespace TeaPacket::Graphics
{
    struct MeshParams
    {
        std::span<unsigned char> vertexData;
        std::span<VariableType> vertexInfo;
        std::span<std::remove_reference_t<decltype(TP_Graphics_MeshIndexList::p[0])>> indexList;

        static_assert(std::is_same_v<
            std::span<std::remove_const_t<std::remove_reference_t<decltype(TP_Graphics_MeshIndexList::p[0])>>>,
            std::span<tp_u32>
            >);
    };
}
