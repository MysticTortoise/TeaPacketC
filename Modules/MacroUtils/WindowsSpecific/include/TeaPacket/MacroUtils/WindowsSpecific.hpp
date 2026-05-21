#pragma once
/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#include <stdexcept>

#include "comdef.h"
#include "winerror.h"

inline void CheckErrorWinCom(HRESULT result)
{
    if (!SUCCEEDED(result))
    {
        const _com_error err(result);
        const LPCSTR errorMessage = err.ErrorMessage();
        throw std::runtime_error(errorMessage);
    }
}