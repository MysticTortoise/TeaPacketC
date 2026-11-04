#pragma once

#include "passes/rename_attr.hpp"

#include "spvpass/ops/OpTypePointer.hpp"

class SpirVPassRenameUniforms : public SpirVPassRenameAttribute
{
public:
    bool IsVarRenamable(const spvpass::OpVariable& var) override
    {
        return var.GetStorageClass() == spv::StorageClass::Uniform;
    }

    [[nodiscard]] const char* name() const override {return "rename_uniform_attrs"; }
    [[nodiscard]] const char* GetVarPrefix() override { return "u"; }
};