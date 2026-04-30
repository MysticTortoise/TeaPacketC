#ifndef TEAPACKET_TESTUTIL_STRING_H
#define TEAPACKET_TESTUTIL_STRING_H

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Types/Numeric.h"
#ifdef __cplusplus
extern "C" {
#endif

tp_bool IsStringEqual(TP_StringView a, TP_StringView b);
TP_StringView StrViewFromStr(TP_String str);
TP_StringView StrViewFromConstStr(const char* msg);

#ifdef __cplusplus
}
#endif
#endif
