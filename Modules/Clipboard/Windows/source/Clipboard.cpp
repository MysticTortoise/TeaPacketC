#include "TeaPacket/Clipboard/Clipboard.h"

#include "ProcessDIBFile.hpp"
#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"

#include "windows.h"
#include "TeaPacket/Memory/Memory.h"

static UINT Types[TP_Clipboard_ContentsType_MAX-1] = {
    CF_TEXT,
    CF_DIB
};

TP_Clipboard_ContentsType TP_Clipboard_GetContentsType()
{
    const int clipboardFormat = GetPriorityClipboardFormat(Types, TP_Clipboard_ContentsType_MAX);

    switch (clipboardFormat)
    {
    case 0:
    case -1:
    default:
        return TP_Clipboard_ContentsType_None;

    case CF_TEXT:
        return TP_Clipboard_ContentsType_Text;
    case CF_DIB:
        return TP_Clipboard_ContentsType_Image;
    }
}

TP_String TP_Clipboard_GetText()
{
    if (!IsClipboardFormatAvailable(CF_TEXT))
        return {};

    if (!OpenClipboard(TP_Window_GetActive()->windowHandle))
        return {};

    const auto textHandle = GetClipboardData(CF_TEXT);
    if (textHandle != nullptr)
    {
        const auto textData = GlobalLock(textHandle);
        if (textData != nullptr)
        {
            // better way?
            const size_t length = strlen(static_cast<char const*>(textData));
            const TP_String str = {
                static_cast<char*>(TP_MemAlloc(length)),
                length
            };
            memcpy(str.p, textData, length);

            GlobalUnlock(textHandle);
            CloseClipboard();
            return str;
        }
    }
    CloseClipboard();
    return {};

}

tp_bool TP_Clipboard_WriteText(const TP_StringView text)
{

    if (!OpenClipboard(TP_Window_GetActive()->windowHandle))
        return tp_false;

    EmptyClipboard();

    HGLOBAL globalHandle = GlobalAlloc(GMEM_MOVEABLE, text.size+1);
    if (globalHandle == nullptr)
    {
        CloseClipboard();
        return tp_false;
    }

    auto globalText = static_cast<unsigned char*>(GlobalLock(globalHandle));
    memcpy(globalText, text.p, text.size);
    globalText[text.size] = '\0';
    GlobalUnlock(globalHandle);
    SetClipboardData(CF_TEXT, globalHandle);

    CloseClipboard();
    return tp_true;

}

TP_Graphics_ImageData TP_Clipboard_GetImageData()
{
    if (!IsClipboardFormatAvailable(CF_DIB))
        return {};

    if (!OpenClipboard(TP_Window_GetActive()->windowHandle))
        return {};

    const auto clipboardHandle = GetClipboardData(CF_DIB);
    TP_Graphics_ImageData imageData{};
    if (clipboardHandle != nullptr && clipboardHandle != INVALID_HANDLE_VALUE)
    {
        const auto dibData = GlobalLock(clipboardHandle);
        if (dibData != nullptr)
        {
            imageData = TeaPacket::Clipboard::Windows::GetImageDataFromDIB(*static_cast<BITMAPINFO*>(dibData));
            GlobalUnlock(clipboardHandle);
        }
    }
    CloseClipboard();
    return imageData;

}

tp_bool TP_Clipboard_WriteImageData(const TP_Graphics_ImageData imageData)
{
    switch (imageData.format)
    {
    case TP_Graphics_Texture_Format_BGRA8:
    case TP_Graphics_Texture_Format_RGBA8:
        break;
    default: return tp_false;
    }

    if (!OpenClipboard(TP_Window_GetActive()->windowHandle))
        return tp_false;

    EmptyClipboard();

    HGLOBAL globalHandle = GlobalAlloc(GMEM_MOVEABLE, TeaPacket::Clipboard::Windows::GetDIBSizeFromImageData(imageData));
    if (globalHandle == nullptr)
    {
        CloseClipboard();
        return tp_false;
    }

    const auto bitmapData = static_cast<BITMAPINFO*>(GlobalLock(globalHandle));
    if (bitmapData)
    {
        TeaPacket::Clipboard::Windows::WriteImageDataToDIB(bitmapData, imageData);
    } else
    {
        CloseClipboard();
        return tp_false;
    }


    GlobalUnlock(globalHandle);
    SetClipboardData(CF_DIB, globalHandle);
    CloseClipboard();
    return tp_true;

}