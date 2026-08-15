#pragma once
#include <windows.h>
#include "TeaPacket/Graphics/Texture/ImageData.h"

namespace TeaPacket::Clipboard::Windows
{
    TP_Graphics_ImageData GetImageDataFromDIB(const BITMAPINFO& DIBInfo);

    size_t GetDIBSizeFromImageData(const TP_Graphics_ImageData& imageData);
    void WriteImageDataToDIB(BITMAPINFO* DIBInfo, const TP_Graphics_ImageData& imageData);
}
