#include "passes/rename_attr.hpp"

spvtools::opt::Pass::Status SpirVPassRenameAttribute::Process()
{
    bool changed = false;

    for (const auto& var : spvpass::OpVariable::GetAllOpVars(*context()))
    {
        if (!IsVarRenamable(var))
        {
            continue;
        }
        for (const auto deco : var.GetAllDecorations())
        {
            if (deco.GetDecorationType() == spv::Decoration::Location)
            {
                var.SetName(GetVarPrefix() + std::to_string(deco.GetDecorationParam(0)));
                changed = true;
                break;
            }
        }
    }

    return changed ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}