#ifndef TEAPACKET_EXTENSIONS_FORMAT_IMAGE_BMP_IMPL_H
#define TEAPACKET_EXTENSIONS_FORMAT_IMAGE_BMP_IMPL_H
#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Endianness/Endian.h"
#include "TeaPacket/Extensions/IStream/IStream.h"
#include "TeaPacket/Graphics/Texture/ImageData.h"
#include "TeaPacket/Graphics/Color.h"
#ifdef __cplusplus
extern "C"
{
#endif
    
typedef enum
{
    TP_Ext_Format_Image_BMP_Type_WinBM = TP_U16_MEMORDER(42,4d),
    TP_Ext_Format_Image_BMP_Type_OS2Bitmap = TP_U16_MEMORDER(42,41),
    TP_Ext_Format_Image_BMP_Type_OS2ColorIcon = TP_U16_MEMORDER(43,49),
    TP_Ext_Format_Image_BMP_Type_OS2ColorPtr = TP_U16_MEMORDER(43,50),
    TP_Ext_Format_Image_BMP_Type_OS2Icon = TP_U16_MEMORDER(49,43),
    TP_Ext_Format_Image_BMP_Type_OS2Ptr = TP_U16_MEMORDER(50,54)
} TP_Ext_Format_Image_BMP_Type;

struct TP_Ext_Format_Image_BMP_FileHeader
{
    tp_u16 type;
    tp_u32 filesize;
    tp_u32 startingAddress;
};

void TP_Extensions_Formats_Image_BMP_ReadHeader(TP_Extension_IStream* istream, struct TP_Ext_Format_Image_BMP_FileHeader* header);


typedef enum
{
    TP_Ext_Format_Image_BMP_DIBHeaderType_OS21 = 12,
    TP_Ext_Format_Image_BMP_DIBHeaderType_OS22 = 64,
    TP_Ext_Format_Image_BMP_DIBHeaderType_OS22V = 16,
    TP_Ext_Format_Image_BMP_DIBHeaderType_NTV1 = 40,
    TP_Ext_Format_Image_BMP_DIBHeaderType_NTV2 = 52,
    TP_Ext_Format_Image_BMP_DIBHeaderType_NTV3 = 56,
    TP_Ext_Format_Image_BMP_DIBHeaderType_NTV4 = 108,
    TP_Ext_Format_Image_BMP_DIBHeaderType_NTV5 = 124
} TP_Ext_Format_Image_BMP_DIBHeaderType;

typedef enum
{
    TP_Ext_Format_Image_BMP_CompressionType_RGB = 0,
    TP_Ext_Format_Image_BMP_CompressionType_RLE8 = 1,
    TP_Ext_Format_Image_BMP_CompressionType_RLE4 = 2,
    TP_Ext_Format_Image_BMP_CompressionType_Bitfields = 3,
    TP_Ext_Format_Image_BMP_CompressionType_JPG = 4,
    TP_Ext_Format_Image_BMP_CompressionType_PNG = 5,
    TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields = 6
} TP_Ext_Format_Image_BMP_CompressionType;

typedef enum
{
    TP_Ext_Format_Image_BMP_ColorSpace_CalibratedByFile = 0,
    TP_Ext_Format_Image_BMP_ColorSpace_sRGB = TP_U32_MEMORDER(42,47,52,73),
    TP_Ext_Format_Image_BMP_ColorSpace_WindowsSpace = TP_Ext_Format_Image_BMP_ColorSpace_sRGB,
    TP_Ext_Format_Image_BMP_ColorSpace_FileName = TP_U32_MEMORDER(4B,4E,49,4C),
    TP_Ext_Format_Image_BMP_ColorSpace_Embedded = TP_U32_MEMORDER(44,45,42,4D)
} TP_Ext_Format_Image_BMP_ColorSpace;

typedef enum
{
    TP_Ext_Format_Image_BMP_ColorIntent_Business = 1,
    TP_Ext_Format_Image_BMP_ColorIntent_Graphics = 2,
    TP_Ext_Format_Image_BMP_ColorIntent_Images = 4,
    TP_Ext_Format_Image_BMP_ColorIntent_Colorimetric = 8
} TP_Ext_Format_Image_BMP_ColorIntent;

typedef struct
{
    TP_Ext_Format_Image_BMP_DIBHeaderType headerType;
    tp_u16 width;
    tp_u16 height;
    TP_Ext_Format_Image_BMP_CompressionType compressionType;
    tp_u32 finalSize;
    tp_u32 colorIndexCount;
    
    struct
    {
        tp_u32 r;
        tp_u32 g;
        tp_u32 b;
        tp_u32 a;
    } colorMasks;
    
    TP_Ext_Format_Image_BMP_ColorSpace colorSpace;
    
    struct
    {
        tp_u32 red[3];
        tp_u32 green[3];
        tp_u32 blue[3];
    } colorEndpoints;
    
    struct
    {
        tp_u16 redWhole;
        tp_u16 redFrac;
        tp_u16 greenWhole;
        tp_u16 greenFrac;
        tp_u16 blueWhole;
        tp_u16 blueFrac;
    } toneCurves;
    
    TP_Ext_Format_Image_BMP_ColorIntent colorIntent;
    tp_u32 iccProfileOffset;
    tp_u32 iccProfileSize;
    
    tp_u8 bitsPerPixel;
    tp_bool topDown;
    
    TP_Graphics_Color8A_List colorTable;
} TP_Ext_Format_Image_BMP_Info;

TP_Ext_Format_Image_BMP_Info TP_Ext_Format_Image_BMP_ReadDIBHeader(TP_Extension_IStream* stream); 

tp_bool TP_Ext_Format_Image_BMP_ValidateDIBHeader(TP_Ext_Format_Image_BMP_Info* info);

void TP_Ext_Format_Image_BMP_ReadColorTable(
        TP_Extension_IStream* stream,
        TP_Ext_Format_Image_BMP_Info* info);

TP_Graphics_ImageData TP_Ext_Format_Image_BMP_ReadImage(
        TP_Extension_IStream* stream,
        const TP_Ext_Format_Image_BMP_Info* info);

void TP_Ext_Format_Image_BMP_SetError(TP_StringView msg);

#ifdef __cplusplus
}
#endif
#endif
