#pragma once

#include "spvpass/ops/OpWrapperBase.hpp"

#include <string>

namespace spvpass
{
    class OpName : public OpWrapperBase
    {
    public:
        explicit constexpr OpName(spvtools::opt::Instruction& instruction):
        OpWrapperBase(instruction, spv::Op::OpName)
        {}

        [[nodiscard]] std::string AsString() const
        {
            return instruction->GetOperand(1).AsString();
        }

        void SetName(const std::string& newName) const
        {
            instruction->SetOperand(1, spvtools::utils::MakeVector(newName));
        }


    };
}