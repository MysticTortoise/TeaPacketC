#ifndef TeaPacket_Extensions_Formats_Image_BMP_H
#define TeaPacket_Extensions_Formats_Image_BMP_H

#include "TeaPacket/Extensions/IStream/IStream.h"
#include "TeaPacket/Graphics/Common/ImageData.h"
#include "TeaPacket/Graphics/Common/Color.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
    TP_Gfx_Color8A_List* colorTable;
} TP_Extensions_Formats_Image_BMP_ReadOptions;

typedef struct TP_Ext_Format_Image_BMP_FileHeader TP_Ext_Format_Image_BMP_FileHeader;

TP_Gfx_ImageData TP_Extensions_Formats_Image_ReadBMP(
    TP_Extension_IStream* data, 
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions);

TP_Gfx_ImageData TP_Extensions_Formats_Image_ReadBMPFromAsset(
    TP_StringView assetPath,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions);


TP_Gfx_ImageData TP_Ext_Format_Image_BMP_ReadDIB(
    TP_Extension_IStream* data,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions, const TP_Ext_Format_Image_BMP_FileHeader* fileHeader);

#ifdef __cplusplus
}
#endif
#endif
