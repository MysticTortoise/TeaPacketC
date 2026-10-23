#pragma once

#include "source/opt/pass.h"


namespace spvpass
{
    template<typename T>
    spvtools::Optimizer& RegisterCustomPass(spvtools::Optimizer& opt)
    {
        return opt.RegisterPass(spvtools::Optimizer::PassToken{std::make_unique<T>()});
    }
}
