#pragma once

#include "source/opt/instruction.h"

namespace spvpass
{
    class OpWrapperBase
    {
    protected:
        spvtools::opt::Instruction* const instruction;

        static constexpr bool IsOfType(spvtools::opt::Instruction& instruction, spv::Op typeToCheck)
        {
            return instruction.opcode() == typeToCheck;
        }

        static constexpr spvtools::opt::Instruction* ValidateInstruction(
            spvtools::opt::Instruction& instruction, spv::Op typeToCheck)
        {
            return IsOfType(instruction, typeToCheck) ? &instruction : nullptr;
        }

        explicit constexpr OpWrapperBase(spvtools::opt::Instruction& instruction,
            spv::Op desiredOpType):
            instruction(ValidateInstruction(instruction, desiredOpType))
        {}

    public:
        virtual ~OpWrapperBase() = default;
        OpWrapperBase() = delete;
        explicit OpWrapperBase(spvtools::opt::Instruction& instruction) = delete;

        [[nodiscard]] constexpr bool IsValid() const
        {
            return instruction != nullptr;
        }

        static std::vector<spvtools::opt::Instruction*> GetAllOpsOfType(
            spvtools::opt::IRContext& context,
            spv::Op desiredOpType)
        {
            std::vector<spvtools::opt::Instruction*> instructions{};
            for (auto& instruction : context.types_values())
            {
                if (instruction.opcode() != desiredOpType)
                    continue;
                instructions.emplace_back(&instruction);
            }
            return instructions;
        }
    };
}