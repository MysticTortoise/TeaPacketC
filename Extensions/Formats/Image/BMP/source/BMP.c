#include "TeaPacket/Extensions/Format/Image/BMP.h"

#include <assert.h>

#include "TeaPacket/Endianness/Conversions.h"
#include "TeaPacket/Extensions/Format/Image/BMP_impl.h"
#include "TeaPacket/Extensions/IStream/IntReading.h"
#include "TeaPacket/MacroUtils/Features.h"


#include "TeaPacket/Extensions/Image/Conversions/Conversions.h"
#include "TeaPacket/Memory/Memory.h"

void TP_Extensions_Formats_Image_BMP_ReadHeader(TP_Extension_IStream* istream,
                                                TP_Ext_Format_Image_BMP_FileHeader* header)
{
    TP_Extension_IStream_Read(istream, sizeof(header->type), header);
    header->filesize = TP_Extension_IStream_Read32LittleEndian(istream);
    TP_Extension_IStream_Skip(istream, 4);
    header->startingAddress = TP_Extension_IStream_Read32LittleEndian(istream);
}

TP_Ext_Format_Image_BMP_Info TP_Ext_Format_Image_BMP_ReadDIBHeader(TP_Extension_IStream* stream)
{
    TP_Ext_Format_Image_BMP_Info info = {0};
    tp_bool earlyExit = tp_false;


    tp_u32 dibHeaderSize;
    TP_Extension_IStream_Read(stream, sizeof(dibHeaderSize), &dibHeaderSize);
    dibHeaderSize = TP_FromU32LittleEndian(dibHeaderSize);

    info.headerType = dibHeaderSize;
    info.colorSpace = TP_Ext_Format_Image_BMP_ColorSpace_sRGB;


    switch (dibHeaderSize)
    {
    case TP_Ext_Format_Image_BMP_DIBHeaderType_OS21:

        info.width = TP_Extension_IStream_Read16LittleEndian(stream);
        info.height = TP_Extension_IStream_Read16LittleEndian(stream);
        TP_Extension_IStream_Skip(stream, 2);
        info.bitsPerPixel = (tp_u8)TP_Extension_IStream_Read16LittleEndian(stream);
        break;

    case TP_Ext_Format_Image_BMP_DIBHeaderType_OS22:
    default:
    case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV1:
    case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV2:
    case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV3:
    case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV4:
    case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV5:
        info.width = (tp_u16)TP_Extension_IStream_Read32LittleEndian(stream);
    {
        tp_u32 readHeight = TP_Extension_IStream_Read32LittleEndian(stream);
        tp_i32 trueHeight;
        memcpy(&trueHeight, &readHeight, sizeof(readHeight));
        if (trueHeight < 0)
        {
            info.topDown = tp_true;
            info.height = (tp_u16)-trueHeight;
        } else
        {
            info.topDown = tp_false;
            info.height = (tp_u16)trueHeight;
        }
    }

        TP_Extension_IStream_Skip(stream, 2);
        info.bitsPerPixel = (tp_u8)TP_Extension_IStream_Read16LittleEndian(stream);
        
        if (dibHeaderSize <= 16)
            break;
        
        info.compressionType = TP_Extension_IStream_Read32LittleEndian(stream);
        if (dibHeaderSize <= 20)
            break;
        
        info.finalSize = TP_Extension_IStream_Read32LittleEndian(stream);
        if (dibHeaderSize <= 24)
            break;
        
        TP_Extension_IStream_Skip(stream, (((8) < (dibHeaderSize - 24)) ? (8) : (dibHeaderSize - 24)));
        if (dibHeaderSize <= 32)
            break;
        info.colorIndexCount = TP_Extension_IStream_Read32LittleEndian(stream);
        if (dibHeaderSize <= 36)
            break;
        TP_Extension_IStream_Skip(stream, 4);
        
        switch (dibHeaderSize)
        {
        case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV1:
        case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV2:
        case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV3:
        case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV4:
        case TP_Ext_Format_Image_BMP_DIBHeaderType_NTV5:
            break;
        default:
            {
                /* os2v2 */
                /* pretty much everything else is useless so we ignore it */
                const size_t toSkip = dibHeaderSize - TP_Ext_Format_Image_BMP_DIBHeaderType_NTV1;
                TP_Extension_IStream_Skip(stream, toSkip);
                earlyExit = tp_true;
            }
        }
        
        if (earlyExit)
            break;

        if (dibHeaderSize <= TP_Ext_Format_Image_BMP_DIBHeaderType_NTV1 && 
            info.compressionType != TP_Ext_Format_Image_BMP_CompressionType_Bitfields &&
            info.compressionType != TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields)
            break;

        TP_Extension_IStream_Read(stream, sizeof(info.colorMasks.r) * 3, &info.colorMasks.r);

#if TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
        info.colorMasks.r = TP_SwapU32(info.colorMasks.r);
        info.colorMasks.g = TP_SwapU32(info.colorMasks.g);
        info.colorMasks.b = TP_SwapU32(info.colorMasks.b);
#endif

        if (dibHeaderSize <= TP_Ext_Format_Image_BMP_DIBHeaderType_NTV2 &&
            info.compressionType != TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields)
            break;
        info.colorMasks.a = TP_Extension_IStream_Read32LittleEndian(stream);

        if (dibHeaderSize <= TP_Ext_Format_Image_BMP_DIBHeaderType_NTV3)
            break;

        info.colorSpace = TP_Extension_IStream_Read32LittleEndian(stream);

        if (info.colorSpace == TP_Ext_Format_Image_BMP_ColorSpace_CalibratedByFile)
        {
            TP_Extension_IStream_Read(stream, 36, &info.colorEndpoints);
            TP_Extension_IStream_Read(stream, 12, &info.toneCurves);
        } else
        {
            TP_Extension_IStream_Skip(stream, 36 + 12);
        }

        if (dibHeaderSize <= TP_Ext_Format_Image_BMP_DIBHeaderType_NTV4)
            break;

        info.colorIntent = TP_Extension_IStream_Read32LittleEndian(stream);
        info.iccProfileOffset = TP_Extension_IStream_Read32LittleEndian(stream);
        info.iccProfileSize = TP_Extension_IStream_Read32LittleEndian(stream);
        TP_Extension_IStream_Skip(stream, 4);
        break;
    }
    return info;

#undef RETURN_WITH_ERROR
}

tp_bool TP_Ext_Format_Image_BMP_ValidateDIBHeader(TP_Ext_Format_Image_BMP_Info* info)
{
    switch (info->bitsPerPixel)
    {
    case 0:
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
    case 24:
    case 32:
        break;
    default: return tp_false;
    }

    if (info->colorIndexCount == 0)
    {
        switch (info->bitsPerPixel)
        {
        case 1:
            info->colorIndexCount = 2;
            break;
        case 2:
            info->colorIndexCount = 4;
            break;
        case 4:
            info->colorIndexCount = 16;
            break;
        case 8:
            info->colorIndexCount = 256;
            break;
        default: break;
        }
    }

    /*if (info->colorSpace != TP_Ext_Format_Image_BMP_ColorSpace_sRGB)
    {
        TP_Ext_Format_Image_BMP_SetError(TP_StrViewFromConstStr("Non sRGB images not yet supported."));
        return tp_false;
    }*/
    
    if (info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_RGB)
    {
        switch (info->bitsPerPixel)
        {
        case 16:
            info->colorMasks.r = 31744;
            info->colorMasks.g = 992;
            info->colorMasks.b = 31;
            info->colorMasks.a = 0;
            break;
        case 24:
            /*info->colorMasks.r = 0x00FF0000;
            info->colorMasks.g = 0x0000FF00;
            info->colorMasks.b = 0x000000FF;
            info->colorMasks.a = 0;
            break;*/
        case 32:
            info->colorMasks.r = 0x00FF0000 ;
            info->colorMasks.g = 0x0000FF00 ;
            info->colorMasks.b = 0x000000FF;
            info->colorMasks.a = 0;
            break;
        default: break;
        }
    }

    return tp_true;
}

void TP_Ext_Format_Image_BMP_ReadColorTable(
    TP_Extension_IStream* stream, TP_Ext_Format_Image_BMP_Info* info)
{
    const tp_bool hasAlpha = info->headerType > TP_Ext_Format_Image_BMP_DIBHeaderType_OS21;
    size_t i;

    assert(sizeof(info->colorTable.p[0]) == 4);
    info->colorTable.size = (size_t)info->colorIndexCount;
    info->colorTable.p = TP_MemAlloc(sizeof(info->colorTable.p[0]) * info->colorTable.size);
    
    if (!hasAlpha)
    {
        /* no reserved */
        TP_Graphics_Color8A* color = info->colorTable.p;
        tp_u8 colors[4];
        for (i = 0; i < info->colorTable.size; i++)
        {
            TP_Extension_IStream_Read(stream, 3, colors);
            color->b = colors[0];
            color->g = colors[1];
            color->r = colors[2];
            color->a = 255;
            color++;
        }
    } else
    {
        /* has reserved */
        TP_Graphics_Color8A* color = info->colorTable.p;
        tp_u8 colors[4];
        for (i = 0; i < info->colorTable.size; i++)
        {
            TP_Extension_IStream_Read(stream, 4, colors);
            color->b = colors[0];
            color->g = colors[1];
            color->r = colors[2];
            color->a = 255;
            color++;
        }
    }
}



void TP_Ext_Format_Image_BMP_SetError(TP_StringView msg)
{
    (void)msg;
    /* TP_LogString(msg);*/
}


TP_Graphics_ImageData TP_Extensions_Formats_Image_ReadBMP(TP_Extension_IStream* data,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions)
{
    TP_Ext_Format_Image_BMP_FileHeader header;
    TP_Ext_Format_Image_BMP_Info info;
    TP_Extensions_Formats_Image_BMP_ReadHeader(data, &header);


    /* READ DIB HEADER */
    info = TP_Ext_Format_Image_BMP_ReadDIBHeader(data);
    if (!TP_Ext_Format_Image_BMP_ValidateDIBHeader(&info))
    {
        const TP_Graphics_ImageData blankData = {0};
        return blankData;
    }
    
    if (info.colorIndexCount > 0)
    {
        TP_Ext_Format_Image_BMP_ReadColorTable(data, &info);
    }
    
    if (readOptions->colorTable != 0 && info.colorIndexCount > 0)
    {
        *readOptions->colorTable = info.colorTable;
    }
    
    TP_Extension_IStream_Seek(data, (ptrdiff_t)header.startingAddress, TP_Assets_Stream_SeekBase_Begin);

    {
        TP_Graphics_ImageData imgData = TP_Ext_Format_Image_BMP_ReadImage(data, &info);
        if (readOptions->colorTable == 0 && info.colorTable.p != 0 && info.bitsPerPixel <= 8)
        {
            void* oldData = imgData.data;
            switch (info.bitsPerPixel)
            {
            case 1:
                imgData = TP_Extensions_Image_Convert_Palette1ToRGBA(&imgData, info.colorTable);
                break;
            case 2:
                imgData = TP_Extensions_Image_Convert_Palette2ToRGBA(&imgData, info.colorTable);
                break;
            case 4:
                imgData = TP_Extensions_Image_Convert_Palette4ToRGBA(&imgData, info.colorTable);
                break;
            case 8:
                imgData = TP_Extensions_Image_Convert_Palette8ToRGBA(&imgData, info.colorTable);
                break;
            default:
                {
                    const TP_Graphics_ImageData blankData = {0};
                    return blankData;
                }
            }
            TP_MemFree(oldData);
            TP_MemFree(info.colorTable.p);
        }

        return imgData;
    }
}

TP_Graphics_ImageData TP_Extensions_Formats_Image_ReadBMPFromAsset(const TP_StringView assetPath,
    TP_Extensions_Formats_Image_BMP_ReadOptions* readOptions)
{
    TP_Extension_IStream stream = TP_Extensions_IStream_StreamFromAsset(assetPath);
    if (!stream.privData)
    {
        const TP_Graphics_ImageData data = {0};
        TP_Ext_Format_Image_BMP_SetError(TP_StrViewFromConstStr("Failed to open file!"));
        return data;
    }

    {
        const TP_Graphics_ImageData data = TP_Extensions_Formats_Image_ReadBMP(&stream, readOptions);
        TP_Extension_IStream_Close(&stream);
        return data;
    }
}
