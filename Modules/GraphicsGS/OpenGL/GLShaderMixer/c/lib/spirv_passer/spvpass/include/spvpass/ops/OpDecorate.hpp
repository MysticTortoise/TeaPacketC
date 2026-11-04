#pragma once

#include "spvpass/ops/OpWrapperBase.hpp"


namespace spvpass
{
    class OpDecorate : public OpWrapperBase
    {
    public:
        explicit constexpr OpDecorate(spvtools::opt::Instruction& instruction):
        OpWrapperBase(instruction, spv::Op::OpDecorate)
        {}

        [[nodiscard]] constexpr spv::Decoration GetDecorationType() const
        {
            return static_cast<spv::Decoration>(instruction->GetSingleWordInOperand(1));
        }

        [[nodiscard]] constexpr uint32_t GetDecorationParam(const unsigned index) const
        {
            return instruction->GetSingleWordInOperand(index + 2);
        }


    };
}