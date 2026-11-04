#pragma once

#include "spvpass/ops/OpType.hpp"

namespace spvpass
{
    class OpTypePointer : public OpType
    {
    public:
        explicit constexpr OpTypePointer(spvtools::opt::Instruction& instruction) :
        OpType(instruction, spv::Op::OpTypePointer)
        {}

        OpTypeBaseType GetBaseType() final
        {
            return OpTypeBaseType::Pointer;
        }

        [[nodiscard]] constexpr spv::StorageClass GetStorageClass() const
        {
            return static_cast<spv::StorageClass>(instruction->GetOperand(0).AsLiteralUint64());
        }




    };
}
