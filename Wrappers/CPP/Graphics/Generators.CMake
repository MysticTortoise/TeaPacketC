TP_get_interface_subdirectory(TP_Graphics_C_Dir Graphics)

TP_EnumGenerator_CPPWrap(
        "${TP_Graphics_C_Dir}/generators/Shader/VariableBaseType.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Graphics/VariableBaseType.hpp"
        "TeaPacket/Graphics/VariableBaseType.h"
        TeaPacket_Graphics_CPP)


TP_EnumGenerator_CPPWrap(
        "${TP_Graphics_C_Dir}/generators/Texture/AvailableMode.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Graphics/Texture/AvailableMode.hpp"
        "TeaPacket/Graphics/Texture/AvailableMode.h"
        TeaPacket_Graphics_CPP
        1)

TP_EnumGenerator_CPPWrap(
        "${TP_Graphics_C_Dir}/generators/Texture/FilterMode.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Graphics/Texture/FilterMode.hpp"
        "TeaPacket/Graphics/Texture/FilterMode.h"
        TeaPacket_Graphics_CPP
        1)

TP_EnumGenerator_CPPWrap(
        "${TP_Graphics_C_Dir}/generators/Texture/Format.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Graphics/Texture/Format.hpp"
        "TeaPacket/Graphics/Texture/Format.h"
        TeaPacket_Graphics_CPP
        1)

TP_EnumGenerator_CPPWrap(
        "${TP_Graphics_C_Dir}/generators/Texture/WrapMode.enum"
        "${PROJECT_SOURCE_DIR}/include/TeaPacket/Graphics/Texture/WrapMode.hpp"
        "TeaPacket/Graphics/Texture/WrapMode.h"
        TeaPacket_Graphics_CPP
        1)