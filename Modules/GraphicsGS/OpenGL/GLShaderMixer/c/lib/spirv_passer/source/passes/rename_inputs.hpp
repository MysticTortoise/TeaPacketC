#pragma once

#include "passes/rename_attr.hpp"

class SpirVPassRenameInputAttrs : public SpirVPassRenameAttribute
{
public:
    bool IsVarRenamable(const spvpass::OpVariable& var) override
    { return var.GetStorageClass() == spv::StorageClass::Input; }
};

class SpirVPassRenameVertexInputs : public SpirVPassRenameInputAttrs
{
public:
    [[nodiscard]] const char* name() const override {return "rename_input_vert_attrs"; }
    [[nodiscard]] const char* GetVarPrefix() override { return "vi"; }
};

class SpirVPassRenameFragmentInputs : public SpirVPassRenameInputAttrs
{
public:
    [[nodiscard]] const char* name() const override {return "rename_input_frag_attrs"; }
    const char* GetVarPrefix() override { return "vo"; }
};