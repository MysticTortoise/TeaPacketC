TP_EnumGenerator(
        "${PROJECT_SOURCE_DIR}/generators/InputButton.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/Button.h"
        TeaPacket_Input_Base)

TP_EnumGenerator(
        "${PROJECT_SOURCE_DIR}/generators/InputAxis.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/Axis.h"
        TeaPacket_Input_Base)

TP_EnumGenerator(
        "${PROJECT_SOURCE_DIR}/generators/ControllerType.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Input/ControllerType.h"
        TeaPacket_Input_Base)