#pragma once

#include "passes/rename_attr.hpp"

#include "spvpass/ops/OpTypePointer.hpp"

class SpirVPassRenameSamplers : public SpirVPassRenameAttribute
{
public:
    bool IsVarRenamable(const spvpass::OpVariable& var) override
    { return var.GetStorageClass() == spv::StorageClass::UniformConstant; }

    [[nodiscard]] const char* name() const override {return "rename_input_vert_attrs"; }
    [[nodiscard]] const char* GetVarPrefix() override { return "t"; }
};