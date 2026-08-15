#include <assert.h>
#include <string.h>

#include "TeaPacket/Extensions/Image/Conversions/Conversions.h"
#include "TeaPacket/Memory/Memory.h"

TP_Graphics_ImageData TP_Extensions_Image_Convert_PaletteNToRGBA(
    const TP_Graphics_ImageData* palettedImage,
    const TP_Graphics_Color8A_List colorList,
    const tp_u8 n)
{
    TP_Graphics_ImageData imageData;
    size_t y, xb, b;
    

    imageData.pitch = palettedImage->width * 4;
    imageData.width = palettedImage->width;
    imageData.height = palettedImage->height;
    imageData.format = TP_Graphics_Texture_Format_RGBA8;
    imageData.data = TP_MemAlloc(imageData.pitch * imageData.height);
    
    for (y = 0; y < imageData.height; y++)
    {
        tp_u32* dstPixel = (tp_u32*)imageData.data + imageData.width * y;
        const tp_byte* srcPixel = ((tp_byte*)palettedImage->data) + palettedImage->pitch * y;
        for (xb = 0; xb < palettedImage->pitch-1; xb++)
        {
            for (b = 0; b < 8/n; b++)
            {
                memcpy(dstPixel, &colorList.p[(*srcPixel >> ((8-n)-(b*n))) & ((1 << n) - 1)], 4);
                dstPixel++;
            }
            srcPixel++;
        }
        /* last byte */
        {
            const size_t bitsLeft = 8/n - ((palettedImage->pitch * 8/n) - imageData.width);
            for (b = 0; b < bitsLeft; b++)
            {
                memcpy(dstPixel, &colorList.p[(*srcPixel >> ((8-n)-(b*n))) & ((1 << n) - 1)], 4);
                dstPixel++;
            }
        }
    }
    
    return imageData;
}


TP_Graphics_ImageData TP_Extensions_Image_Convert_Palette1ToRGBA(
    const TP_Graphics_ImageData* palettedImage,
    const TP_Graphics_Color8A_List colorList)
{
    assert(palettedImage->format == TP_Graphics_Texture_Format_R1);
    return TP_Extensions_Image_Convert_PaletteNToRGBA(palettedImage, colorList, 1);
}

TP_Graphics_ImageData TP_Extensions_Image_Convert_Palette2ToRGBA(
    const TP_Graphics_ImageData* palettedImage,
    const TP_Graphics_Color8A_List colorList)
{
    assert(palettedImage->format == TP_Graphics_Texture_Format_R2);
    return TP_Extensions_Image_Convert_PaletteNToRGBA(palettedImage, colorList, 2);
}

TP_Graphics_ImageData TP_Extensions_Image_Convert_Palette4ToRGBA(
    const TP_Graphics_ImageData* palettedImage,
    const TP_Graphics_Color8A_List colorList)
{
    assert(palettedImage->format == TP_Graphics_Texture_Format_R4);
    return TP_Extensions_Image_Convert_PaletteNToRGBA(palettedImage, colorList, 4);
}

TP_Graphics_ImageData TP_Extensions_Image_Convert_Palette8ToRGBA(
    const TP_Graphics_ImageData* palettedImage,
    const TP_Graphics_Color8A_List colorList)
{
    assert(palettedImage->format == TP_Graphics_Texture_Format_R8);
    return TP_Extensions_Image_Convert_PaletteNToRGBA(palettedImage, colorList, 8);
}
