#pragma once

#include <GameInput.h>
#include <wrl/client.h>

#undef max // stupid ass windows header

namespace TeaPacket::Input
{
    inline Microsoft::WRL::ComPtr<GameInput::v3::IGameInput> gameInput;

    constexpr GameInput::v3::GameInputKind GameInputKindAny = static_cast<GameInput::v3::GameInputKind>(0x000FFFFF);
}
