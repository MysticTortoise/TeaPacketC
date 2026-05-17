TP_get_interface_subdirectory(TP_Input_C_Dir Input)

TP_EnumGenerator_CPPWrap(
        "${TP_Input_C_Dir}/generators/ControllerType.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/ControllerType.hpp"
        "TeaPacket/Input/ControllerType.h"
        TeaPacket_Input_CPP)

TP_EnumGenerator_CPPWrap(
        "${TP_Input_C_Dir}/generators/InputAxis.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/Axis.hpp"
        "TeaPacket/Input/Axis.h"
        TeaPacket_Input_CPP)

TP_EnumGenerator_CPPWrap(
        "${TP_Input_C_Dir}/generators/InputButton.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/Button.hpp"
        "TeaPacket/Input/Button.h"
        TeaPacket_Input_CPP)