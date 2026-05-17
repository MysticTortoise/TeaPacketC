#pragma once
#include <cassert>

#include "TeaPacket/Input/Input.h"

#include "TeaPacket/Input/Button.hpp"
#include "TeaPacket/Input/Axis.hpp"
#include "TeaPacket/Input/ControllerType.hpp"

#include "TeaPacket/Types/String.hpp"

#include

namespace TeaPacket::Input
{
    typedef TP_Input_Slot InputSlotID;
    constexpr InputSlotID NoSlot = TP_Input_NoControllerSlot;

    inline bool Init()
    {
        return TP_Input_Init();
    }

    inline void DeInit()
    {
        return TP_Input_DeInit();
    }

    inline void UpdateControllers()
    {
        TP_Input_UpdateControllers();
    }

    inline void PollSlot(const InputSlotID slot)
    {
        TP_Input_PollSlot(slot);
    }

    inline bool IsSlotConnected(const InputSlotID slot)
    {
        return TP_Input_IsConnected(slot);
    }

    inline bool IsButtonPressed(const InputSlotID slot, const Button button)
    {
        return TP_Input_IsButtonPressed(slot, static_cast<TP_Input_Button>(button));
    }

    inline float GetAxis(const InputSlotID slot, const Axis axis)
    {
        return TP_Input_GetAxis(slot, static_cast<TP_Input_Axis>(axis));
    }

    inline bool IsButtonSupported(const InputSlotID slot, const Button button)
    {
        return TP_Input_IsButtonSupported(slot, static_cast<TP_Input_Button>(button));
    }

    inline bool IsAxisSupported(const InputSlotID slot, const Axis axis)
    {
        return TP_Input_IsAxisSupported(slot, static_cast<TP_Input_Axis>(axis));
    }

    inline TPString GetControllerName(const InputSlotID slot)
    {
        return TPString(TP_Input_GetControllerName(slot));
    }

    inline InputSlotID GetLastPressed(const ControllerType filter)
    {
        return TP_Input_GetLastSlotPressed(static_cast<TP_Input_ControllerType>(filter));
    }

    inline InputSlotID GetSlotCount()
    {
        return TP_Input_GetSlotCount();
    }

    class InputSlotClass
    {
    public:
        const InputSlotID id;

        explicit InputSlotClass(const InputSlotID id):id(id)
        {
            assert(id != NoSlot);
        }

        void Poll() const
        {
            PollSlot(id);
        }

        [[nodiscard]] bool IsConnected() const
        {
            return IsSlotConnected(id);
        }

        [[nodiscard]] bool IsButtonPressed(const Button button) const
        {
            return Input::IsButtonPressed(id, button);
        }

        [[nodiscard]] float GetAxisValue(const Axis axis) const
        {
            return GetAxis(id, axis);
        }

        [[nodiscard]] bool IsButtonSupported(const Button button) const
        {
            return Input::IsButtonPressed(id, button);
        }

        [[nodiscard]] bool IsAxisSupported(const Axis axis) const
        {
            return Input::IsAxisSupported(id, axis);
        }

        [[nodiscard]] TPString GetName() const
        {
            return GetControllerName(id);
        }

        // STATICS
        [[nodiscard]] static InputSlotClass GetLastSlotPressed(const ControllerType filter)
        {
            return InputSlotClass(Input::GetLastPressed(filter));
        }
    };

}
