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
        for (const auto& deco : var.GetAllDecorations())
        {
            uint32_t loc = 0xFFFFFFFF;
            if (deco.GetDecorationType() == spv::Decoration::Location ||
                deco.GetDecorationType() == spv::Decoration::Binding)
            {
                loc = deco.GetDecorationParam(0);
            }
            if (loc != 0xFFFFFFF)
            {
                var.SetName(GetVarPrefix() + std::to_string(loc));
                changed = true;
                break;
            }
        }
    }

    return changed ? Status::SuccessWithChange : Status::SuccessWithoutChange;
}