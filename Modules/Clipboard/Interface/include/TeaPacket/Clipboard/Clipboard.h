#ifndef TEAPACKET_CLIPBOARD_H
#define TEAPACKET_CLIPBOARD_H

#include "TeaPacket/Clipboard/ContentsType.h"

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Graphics/Texture/ImageData.h"
#include "TeaPacket/Types/Numeric.h"

#ifdef __cplusplus
extern "C"
{
#endif

TP_Clipboard_ContentsType TP_Clipboard_GetContentsType(void);

TP_String TP_Clipboard_GetText(void);
tp_bool TP_Clipboard_WriteText(TP_StringView text);

TP_Graphics_ImageData TP_Clipboard_GetImageData(void);
tp_bool TP_Clipboard_WriteImageData(TP_Graphics_ImageData imageData);

#ifdef __cplusplus
}
#endif
#endif
