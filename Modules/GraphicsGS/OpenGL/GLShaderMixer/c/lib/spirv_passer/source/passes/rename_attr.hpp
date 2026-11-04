#pragma once

#include "source/opt/pass.h"
#include "spvpass/ops/OpVariable.hpp"

class SpirVPassRenameAttribute : public spvtools::opt::Pass
{
public:
    virtual bool IsVarRenamable(const spvpass::OpVariable& var) = 0;
    virtual const char* GetVarPrefix() = 0;

protected:
    Status Process() override;
};