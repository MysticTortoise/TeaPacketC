#pragma once

#include "passes/rename_attr.hpp"

class SpirVPassRenameOutputAttrs : public SpirVPassRenameAttribute
{
public:
    bool IsVarRenamable(const spvpass::OpVariable& var) override
    {
        return var.GetStorageClass() == spv::StorageClass::Output;
    }
};

class SpirVPassRenameVertexOutputs : public SpirVPassRenameOutputAttrs
{
public:
    [[nodiscard]] const char* name() const override {return "rename_output_vert_attrs"; }
    [[nodiscard]] const char* GetVarPrefix() override { return "vo"; }
};

class SpirVPassRenameFragmentOutputs : public SpirVPassRenameOutputAttrs
{
public:
    [[nodiscard]] const char* name() const override {return "rename_output_frag_attrs"; }
    const char* GetVarPrefix() override { return "po"; }
};