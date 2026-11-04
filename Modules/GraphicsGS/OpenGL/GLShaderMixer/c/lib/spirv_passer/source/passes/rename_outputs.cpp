#include "passes/rename_outputs.hpp"

#include "spvpass/ops/OpDecorate.hpp"
#include "spvpass/ops/OpName.hpp"
#include "spvpass/ops/OpVariable.hpp"

spvtools::opt::Pass::Status SpirVPassRenameOutputs::Process()
{
    bool changed = false;

    for (const auto& var : spvpass::OpVariable::GetAllOpVars(*context()))
    {
        if (var.GetStorageClass() != spv::StorageClass::Output)
        {
            continue;
        }
        for (const auto deco : var.GetAllDecorations())
        {
            if (deco.GetDecorationType() == spv::Decoration::Location)
            {
                var.SetName("o" + std::to_string(deco.GetDecorationParam(0)));
                changed = true;
                break;
            }
        }
    }

    return changed ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}
