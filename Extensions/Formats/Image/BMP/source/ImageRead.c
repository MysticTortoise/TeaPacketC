#include <string.h>

#include "TeaPacket/Endianness/BitCounting.h"
#include "TeaPacket/Endianness/Int24.h"
#include "TeaPacket/Extensions/Format/Image/BMP_impl.h"
#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Logging/Logging.h"

static void Clear32BPPAlpha(TP_Gfx_ImageData image)
{
    tp_byte* ptr = (tp_byte*)image.data + 3;
    size_t i;
    for (i = 0; i < image.width * image.height; i++)
    {
        *ptr = 255;
        ptr += 4;
    }
}

static TP_Gfx_ImageData Read32BPP_Easy(TP_Extension_IStream* stream,
                                            const TP_Ext_Format_Image_BMP_Info* info,
                                            TP_Gfx_ImageData image)
{
    if (info->topDown)
    {
        /* clean read */
        TP_Extension_IStream_Read(stream, image.pitch * image.height, image.data);
    } else
    {
        /* top to bottom */
        tp_byte* curDest = (tp_byte*)image.data + (image.pitch * (image.height - 1));
        size_t y;
        for (y = 0; y < image.height; y++)
        {
            TP_Extension_IStream_Read(stream, image.pitch, curDest);
            curDest -= image.pitch;
        }
    }

    if (info->compressionType != TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields && info->colorMasks.a == 0)
    {
        Clear32BPPAlpha(image);
    }

    return image;
}

// static TP_Graphics_ImageData Read16BPP_Easy(TP_Extension_IStream* stream,
//                                             const TP_Ext_Format_Image_BMP_Info* info,
//                                             TP_Graphics_ImageData image)
// {
//     image.pitch = image.width * 2;
//     if (info->topDown)
//     {
//         /* clean read */
//         TP_Extension_IStream_Read(stream, image.pitch * image.height, image.data);
//     } else
//     {
//         /* top to bottom */
//         tp_byte* curDest = (tp_byte*)image.data + (image.pitch * (image.height - 1));
//         size_t y;
//         for (y = 0; y < image.height; y++)
//         {
//             TP_Extension_IStream_Read(stream, image.pitch, curDest);
//             curDest -= image.pitch;
//         }
//     }
//
//     return image;
// }


static TP_Gfx_ImageData ReadTrueColor(TP_Extension_IStream* stream,
                                           const TP_Ext_Format_Image_BMP_Info* info)
{
    TP_Gfx_ImageData image;
    const size_t bytes = info->bitsPerPixel / 8;
    tp_u8 pixelColors[4] = {0};
    tp_u32 masks[4];
    tp_u8 shiftAmounts[4] = {0};
    float maxVals[4] = {0};
    const tp_bool hasAlpha = info->colorMasks.a != 0;
    const tp_u8 channelCount = hasAlpha ? 4 : 3;
    tp_byte* colorBuffer = malloc(bytes);
    tp_u8 i, j;
    tp_u32 color;
    const size_t srcStride = ((((info->width * info->bitsPerPixel) + 31) & ~31) >> 3);
    const size_t srcStrideSkipNeeded = srcStride - (info->width * bytes);
    size_t x, y;

    image.height = info->height;
    image.width = info->width;
    image.pitch = (tp_u32)(info->width * 4);
    image.data = TP_MemAlloc(image.width * image.pitch);


    if (info->bitsPerPixel == 32) /* check for easy 32bpp */
    {
        if (info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_RGB)
        {
            image.format = TP_Gfx_Image_Format_BGRA8;
            return Read32BPP_Easy(stream, info, image);
        }

        if (
            info->colorMasks.r == 0x00FF0000 &&
            info->colorMasks.g == 0x0000FF00 &&
            info->colorMasks.b == 0x000000FF
        )
        {
            image.format = TP_Gfx_Image_Format_BGRA8;
            return Read32BPP_Easy(stream, info, image);
        }

        if (
            info->colorMasks.r == 0x000000FF &&
            info->colorMasks.g == 0x0000FF00 &&
            info->colorMasks.b == 0x00FF0000
        )
        {
            image.format = TP_Gfx_Image_Format_BGRA8;
            return Read32BPP_Easy(stream, info, image);
        }
    }
    
    /*if (info->bitsPerPixel == 16)
    {
        if (info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_RGB)
        {
            image.format = TP_Graphics_Texture_Format_RGB5A1;
            if (
            info->colorMasks.r == 0x001F &&
            info->colorMasks.g == 0x03E0 &&
            info->colorMasks.b == 0x7C00
        )
            {
                return Read16BPP_Easy(stream, info, image);
            }
        }
    } */


    /* Do it the hard way - bitfield parsing */
    image.format = TP_Gfx_Image_Format_RGBA8;

    masks[0] = info->colorMasks.r;
    masks[1] = info->colorMasks.g;
    masks[2] = info->colorMasks.b;
    masks[3] = info->colorMasks.a;



    for (i = 0; i < channelCount; i++)
    {
        shiftAmounts[i] = TP_Bit_CountTrailingZeros(masks[i]);
        maxVals[i] = (float)(masks[i] >> shiftAmounts[i]);
        TP_LogULong(masks[i]);
        masks[i] = (tp_u32)maxVals[i];
        TP_LogULong(masks[i]);
    }

    for (y = 0; y < image.height; y++)
    {
        tp_u32* pixel;
        if (info->topDown)
        {
            pixel = (tp_u32*)image.data + image.width * y;
        } else
        {
            pixel = (tp_u32*)image.data + image.width * (image.height - y - 1);
        }
        
        for (x = 0; x < image.width; x++)
        {
            TP_Extension_IStream_Read(stream, bytes, colorBuffer);
            switch (bytes)
            {
            case 2:
                color = (tp_u32)TP_FromU16LittleEndian(*(tp_u16*)colorBuffer); break;
            case 3:
#if TP_ENDIAN_NATIVE == TP_ENDIAN_BIG
                {
                    const tp_byte tmp = colorBuffer[0];
                    colorBuffer[0] = colorBuffer[2];
                    colorBuffer[2] = tmp;
                }
#endif
                color = TP_Bit_FromU24(colorBuffer); break;
            case 4:
                color = TP_FromU32LittleEndian(*(tp_u32*)colorBuffer); break;
            default:
                TP_Ext_Format_Image_BMP_SetError(TP_StrViewFromConstStr("unknown bits"));
                return image;
            }
            for (j = 0; j < 4; j++)
            {
                pixelColors[j] = (tp_u8)((float)(color >> shiftAmounts[j] & masks[j]) / maxVals[j] * 255);
            }
            memcpy(pixel, pixelColors, 4);
            pixel++;
        }
        
        if (y == image.height-1u)
            break;
        TP_Extension_IStream_Skip(stream, srcStrideSkipNeeded);
    }

    if (info->compressionType != TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields && info->colorMasks.a == 0)
    {
        Clear32BPPAlpha(image);
    }

    return image;
}

static TP_Gfx_ImageData ReadPaletted(TP_Extension_IStream* stream,  const TP_Ext_Format_Image_BMP_Info* info)
{
    TP_Gfx_ImageData image;
    size_t y;
    const size_t srcStride = ((info->width * info->bitsPerPixel + 31) & ~31) >> 3;
    const tp_u32 pitch = (tp_u32)((double)info->width / (8.0/(double)info->bitsPerPixel)+1);
    const size_t srcStrideSkipNeeded = srcStride - pitch;

    image.height = info->height;
    image.width = info->width;
    
    switch (info->bitsPerPixel)
    {
    case 1:
        image.format = TP_Gfx_Image_Format_R1;
        break;
    case 2:
        image.format = TP_Gfx_Image_Format_R2;
        break;
    case 4:
        image.format = TP_Gfx_Image_Format_R4;
        break;
    case 8:
        image.format = TP_Gfx_Image_Format_R8;
        break;
    default: 
        TP_Ext_Format_Image_BMP_SetError(TP_StrViewFromConstStr("Invalid bpp for paletted image"));
        image.format = 0;
        image.pitch = 0;
        image.data = 0;
        return image;
    }
    
    image.pitch = pitch;
    image.data = TP_MemAlloc(image.height * image.pitch);
    
    for (y = 0; y < image.height; y++)
    {
        tp_byte* row;
            
        if (info->topDown)
        {
            row = (tp_byte*)image.data + image.pitch * y;
        } else
        {
            row = (tp_byte*)image.data + image.pitch * (image.height - y - 1);
        }
        TP_Extension_IStream_Read(stream, image.pitch, row);
        
        if (y == image.height-1u)
            break;
        TP_Extension_IStream_Skip(stream, srcStrideSkipNeeded);
    }
    
    return image;
}

TP_Gfx_ImageData TP_Ext_Format_Image_BMP_ReadImage(TP_Extension_IStream* stream,
                                                        const TP_Ext_Format_Image_BMP_Info* info)
{
    const TP_Gfx_ImageData failData = {0};

    if (info->bitsPerPixel <= 8)
    {
        return ReadPaletted(stream, info);
    }
    
    if (info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_RGB
        ||
        info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_Bitfields
        ||
        info->compressionType == TP_Ext_Format_Image_BMP_CompressionType_AlphaBitfields
    )
    {
        return ReadTrueColor(stream, info);
    }

    return failData;
}
