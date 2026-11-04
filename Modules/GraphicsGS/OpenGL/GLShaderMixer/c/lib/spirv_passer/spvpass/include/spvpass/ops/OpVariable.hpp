#pragma once

#include "source/opt/ir_context.h"
#include "spvpass/ops/OpDecorate.hpp"
#include "spvpass/ops/OpName.hpp"
#include "spvpass/ops/OpWrapperBase.hpp"

namespace spvpass
{
    class OpVariable : public OpWrapperBase
    {
    public:
        explicit constexpr OpVariable(spvtools::opt::Instruction& instruction):
        OpWrapperBase(instruction, spv::Op::OpVariable)
        {}

        // taken from convert_to_sampled_image_pass.h in spirv-tools.
        [[nodiscard]] constexpr spv::StorageClass GetStorageClass() const
        {
            assert(IsValid());

            const spvtools::opt::analysis::Pointer* const type = GetType()->AsPointer();

            return type ? type->storage_class() : spv::StorageClass::Max;
        }

        [[nodiscard]] constexpr spvtools::opt::analysis::Type* GetType() const
        {
            assert(IsValid());
            return instruction->context()->get_type_mgr()->GetType(GetTypeID());
        }

        [[nodiscard]] constexpr uint32_t GetVarID() const
        {
            assert(IsValid());
            return instruction->result_id();
        }

        [[nodiscard]] constexpr uint32_t GetTypeID() const
        {
            return instruction->GetOperand(0).AsId();
        }

        [[nodiscard]] OpName GetName() const
        {
            for (auto& instruction : instruction->context()->debugs2())
            {
                if (instruction.opcode() != spv::Op::OpName)
                    continue;
                uint32_t id = instruction.GetOperand(0).AsId();
                if (id != GetVarID())
                    continue;

                return OpName(instruction);
            }
            throw std::out_of_range("Could not find name!");
        }

        void SetName(const std::string& newName) const
        {
            GetName().SetName(newName);
        }

        [[nodiscard]] std::vector<OpDecorate> GetAllDecorations() const
        {
            std::vector<OpDecorate> decs{};
            for (const auto instr :
                instruction->context()->get_decoration_mgr()->GetDecorationsFor(GetVarID(), true))
            {
                decs.emplace_back(*instr);
            }
            return decs;
        }

        static std::vector<OpVariable> GetAllOpVars(spvtools::opt::IRContext& context)
        {
            std::vector<OpVariable> vars{};
            for (const auto instruction : GetAllOpsOfType(context, spv::Op::OpVariable))
            {
                vars.emplace_back(*instruction);
            }
            return vars;
        }
    };
}
