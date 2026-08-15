#include "ProcessDIBFile.hpp"

#include "TeaPacket/Memory/Memory.h"

#include <fstream>

using namespace TeaPacket::Clipboard;

TP_Graphics_ImageData Windows::GetImageDataFromDIB(const BITMAPINFO& DIBInfo)
{
    TP_Graphics_ImageData imageData{};

    imageData.width = static_cast<tp_u16>(DIBInfo.bmiHeader.biWidth);
    imageData.height = static_cast<tp_u16>(abs(DIBInfo.bmiHeader.biHeight));

    switch (DIBInfo.bmiHeader.biCompression)
    {
    case BI_RGB:
    case BI_BITFIELDS:
        switch (DIBInfo.bmiHeader.biBitCount)
        {
        case 32: // 32 bit rgba
            {
                if (DIBInfo.bmiHeader.biClrUsed) // not yet supported
                    return {};

                imageData.format = TP_Graphics_Texture_Format_BGRA8;
                imageData.pitch = imageData.width * 4;
                imageData.data = TP_MemAlloc(imageData.width * imageData.height * 4);

                auto srcData = reinterpret_cast<const tp_byte*>(&DIBInfo) + DIBInfo.bmiHeader.biSize;
                if (DIBInfo.bmiHeader.biCompression == BI_BITFIELDS)
                {
                    constexpr RGBQUAD ExpectedBitfields[3] = { //TODO: Add support for RGBA instead, and other formats maybe?
                        {0, 0, 255, 0},
                        {0, 255, 0, 0},
                        {255, 0, 0, 0},
                    };
                    for (size_t i = 0; i < sizeof(ExpectedBitfields); i++) // NOLINT(*-sizeof-expression)
                    {
                        const auto byteA = ((tp_byte*)&ExpectedBitfields)[i];
                        if (byteA != *srcData)
                            return {};
                        srcData++;
                    }
                }
                if (DIBInfo.bmiHeader.biHeight < 0)
                {
                    auto destData = static_cast<tp_byte*>(imageData.data);
                    for (tp_u16 i = 0; i < imageData.height; i++)
                    {
                        memcpy(destData, srcData, imageData.pitch);
                        srcData += GDI_DIBWIDTHBYTES(DIBInfo.bmiHeader);
                        destData += imageData.pitch;
                    }
                } else
                {
                    auto destData = static_cast<tp_byte*>(imageData.data) + (imageData.pitch * (imageData.height-1));
                    for (tp_u16 i = 0; i < imageData.height; i++)
                    {
                        memcpy(destData, srcData, imageData.pitch);
                        srcData += GDI_DIBWIDTHBYTES(DIBInfo.bmiHeader);
                        destData -= imageData.pitch;
                    }
                }
            }
        default: break;
        }
    default:
        break;
    }
    return imageData;
}

size_t Windows::GetDIBSizeFromImageData(const TP_Graphics_ImageData& imageData)
{
    switch (imageData.format)
    {
    case TP_Graphics_Texture_Format_BGRA8:
    case TP_Graphics_Texture_Format_RGBA8:
        return (imageData.width * imageData.height * 4) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 3);
    default: return 0;
    }
}

void Windows::WriteImageDataToDIB(BITMAPINFO* DIBInfo, const TP_Graphics_ImageData& imageData)
{
    tp_byte* curPtr = reinterpret_cast<tp_byte*>(DIBInfo);

    // Write header
    auto* const header = reinterpret_cast<BITMAPINFOHEADER*>(curPtr);
    header->biSize = 40;
    header->biPlanes = 1;
    header->biXPelsPerMeter = 2835;
    header->biYPelsPerMeter = 2835;

    std::ofstream bmpFile("test.bmp", std::ios::binary | std::ios::out);
#pragma pack(push, 1)
    struct
    {
        char headerName[2];
        tp_u32 bmpSize;
        tp_u32 unused;
        tp_u32 pixOffset;
    } BITMAPHEADER;
#pragma pack(pop)
    BITMAPHEADER.headerName[0] = 0x42;
    BITMAPHEADER.headerName[1] = 0x4D;
    BITMAPHEADER.bmpSize = (tp_u32)(sizeof(BITMAPHEADER) + GetDIBSizeFromImageData(imageData));
    BITMAPHEADER.unused = 0;
    BITMAPHEADER.pixOffset = sizeof(BITMAPHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBQUAD) * 3);
    bmpFile.write(reinterpret_cast<const char*>(&BITMAPHEADER), sizeof(BITMAPHEADER));



    switch (imageData.format)
    {
    case TP_Graphics_Texture_Format_RGBA8:
    case TP_Graphics_Texture_Format_BGRA8:
        {
            header->biWidth = imageData.width;
            header->biHeight = -imageData.height;
            header->biBitCount = 32;
            header->biCompression = BI_BITFIELDS;
            header->biSizeImage = imageData.width * imageData.height * 4;
            header->biClrUsed = 0;
            header->biClrImportant = 0;
        }
        break;
    default:
        return;
    }
    bmpFile.write(reinterpret_cast<const char*>(header), sizeof(BITMAPINFOHEADER));

    curPtr += sizeof(BITMAPINFOHEADER);

    if (header->biCompression == BI_BITFIELDS)
    {
        const auto bitfields = reinterpret_cast<DWORD*>(curPtr);
        // Write BITFIELDS
        switch (imageData.format)
        {
        case TP_Graphics_Texture_Format_BGRA8:
            bitfields[0] = 0x00'FF'00'00; // red
            bitfields[1] = 0x00'00'FF'00; // green
            bitfields[2] = 0x00'00'00'FF; // blue
            break;
        case TP_Graphics_Texture_Format_RGBA8:
            bitfields[0] = 0x00'00'00'FF; // red
            bitfields[1] = 0x00'00'FF'00; // green
            bitfields[2] = 0x00'FF'00'00; // blue
            break;
        default: return;
        }
        curPtr += sizeof(DWORD) * 3;
        bmpFile.write(reinterpret_cast<const char*>(bitfields), sizeof(DWORD)*3);
    }

    // data time
    switch (imageData.format)
    {
    case TP_Graphics_Texture_Format_RGBA8:
    case TP_Graphics_Texture_Format_BGRA8:
        memcpy(curPtr, imageData.data, imageData.width * imageData.height * 4);
        break;
    }
    bmpFile.write(reinterpret_cast<const char*>(curPtr), imageData.width * imageData.height * 4);
    bmpFile.close();
}
