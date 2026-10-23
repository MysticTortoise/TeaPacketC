#pragma once

#include "spvpass/ops/OpWrapperBase.hpp"

#include <string>

namespace spvpass
{
    enum class OpTypeBaseType
    {
        Pointer,
    };

    class OpType : public OpWrapperBase
    {
    protected:
        explicit constexpr OpType(spvtools::opt::Instruction& instruction,
            spv::Op desiredOpType):OpWrapperBase(instruction, desiredOpType)
        {}

    public:
        explicit OpType() = delete;

        [[nodiscard]] virtual OpTypeBaseType GetBaseType() = 0;
    };
}