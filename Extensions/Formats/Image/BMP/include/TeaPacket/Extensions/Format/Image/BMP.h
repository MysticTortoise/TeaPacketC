#ifndef TEAPACKET_EXTENSIONS_FORMAT_IMAGE_BMP_H
#define TEAPACKET_EXTENSIONS_FORMAT_IMAGE_BMP_H

#include "TeaPacket/Extensions/IStream/IStream.h"
#include "TeaPacket/Graphics/Texture/ImageData.h"
#include "TeaPacket/Graphics/Color.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    TP_Graphics_Color8A_List* colorTable;
} TP_Extensions_Formats_Image_BMP_ReadOptions;

typedef struct TP_Ext_Format_Image_BMP_FileHeader TP_Ext_Format_Image_BMP_FileHeader;

TP_Graphics_ImageData TP_Extensions_Formats_Image_ReadBMP(
    TP_Extension_IStream* data, 
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions);

TP_Graphics_ImageData TP_Extensions_Formats_Image_ReadBMPFromAsset(
    TP_StringView assetPath,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions);


TP_Graphics_ImageData TP_Ext_Format_Image_BMP_ReadDIB(
    TP_Extension_IStream* data,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions, const TP_Ext_Format_Image_BMP_FileHeader* fileHeader);

#ifdef __cplusplus
}
#endif
#endif
