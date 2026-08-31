#ifndef TEAPACKET_EXTENSIONS_IMAGE_CONVERSIONS_H
#define TEAPACKET_EXTENSIONS_IMAGE_CONVERSIONS_H

#include "TeaPacket/Graphics/Common/ImageData.h"
#include "TeaPacket/Graphics/Common/Color.h"

#ifdef __cplusplus
extern "C"
{
#endif

TP_Gfx_ImageData TP_Extensions_Image_Convert_Palette1ToRGBA(
    const TP_Gfx_ImageData* palettedImage,
    TP_Gfx_Color8A_List colorList);

TP_Gfx_ImageData TP_Extensions_Image_Convert_Palette2ToRGBA(
    const TP_Gfx_ImageData* palettedImage,
    TP_Gfx_Color8A_List colorList);

TP_Gfx_ImageData TP_Extensions_Image_Convert_Palette4ToRGBA(
    const TP_Gfx_ImageData* palettedImage,
    TP_Gfx_Color8A_List colorList);

TP_Gfx_ImageData TP_Extensions_Image_Convert_Palette8ToRGBA(
    const TP_Gfx_ImageData* palettedImage,
    TP_Gfx_Color8A_List colorList);

#ifdef __cplusplus
}
#endif
#endif