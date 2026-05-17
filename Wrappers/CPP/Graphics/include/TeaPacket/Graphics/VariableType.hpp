#pragma once
#include "TeaPacket/Graphics/VariableType.h"

#include "TeaPacket/Graphics/VariableBaseType.hpp"

namespace TeaPacket::Graphics
{
    struct VariableType
    {
        VariableBaseType baseType;
        tp_u8 amount;

        [[nodiscard]] size_t GetSize() const
        {
            return TP_Graphics_ShaderVar_GetSize({
                static_cast<TP_Graphics_VariableBaseType>(baseType),
                amount
            });
        }
    };

    static_assert(sizeof(VariableType) == sizeof(TP_Graphics_VariableType));
    static_assert(offsetof(VariableType, baseType) == offsetof(TP_Graphics_VariableType, baseType));
    static_assert(offsetof(VariableType, amount) == offsetof(TP_Graphics_VariableType, amount));
    static_assert(std::is_same_v<std::underlying_type_t<decltype(VariableType::baseType)>, std::underlying_type_t<decltype(TP_Graphics_VariableType::baseType)>>);
    static_assert(std::is_same_v<decltype(VariableType::amount), decltype(TP_Graphics_VariableType::amount)>);
}