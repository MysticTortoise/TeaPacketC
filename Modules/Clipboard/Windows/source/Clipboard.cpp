#include "TeaPacket/Clipboard/Clipboard.h"

#include <cassert>

#include "TeaPacket/Window/PlatformWindow.hpp"
#include "TeaPacket/Window/Window.h"

#include "windows.h"
#include "TeaPacket/Extensions/Format/Image/BMP.h"
#include "TeaPacket/Extensions/Format/Image/BMP_impl.h"
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

TP_Gfx_ImageData TP_Clipboard_GetImageData()
{
    if (!IsClipboardFormatAvailable(CF_DIB))
        return {};

    if (!OpenClipboard(TP_Window_GetActive()->windowHandle))
        return {};

    const auto clipboardHandle = GetClipboardData(CF_DIB);
    TP_Gfx_ImageData imageData{};

    if (clipboardHandle != nullptr && clipboardHandle != INVALID_HANDLE_VALUE)
    {
        const auto dibData = GlobalLock(clipboardHandle);
        TP_Extension_IStream stream = TP_Extensions_IStream_StreamFromMemory({static_cast<const tp_byte*>(dibData), 0});
        if (dibData != nullptr)
        {
            constexpr TP_Ext_Format_Image_BMP_FileHeader fileHeader{
                TP_U16_MEMORDER(42, 4D),
                0,
                0
            };
            TP_Extensions_Formats_Image_BMP_ReadOptions opts{};
            imageData = TP_Ext_Format_Image_BMP_ReadDIB(&stream, &opts, &fileHeader);
            GlobalUnlock(clipboardHandle);
        }
    }
    CloseClipboard();
    return imageData;

}

tp_bool TP_Clipboard_WriteImageData(const TP_Gfx_ImageData imageData)
{
    (void)imageData;
    assert(0);
    // TODO: Implement
    return tp_true;

}