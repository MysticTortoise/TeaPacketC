#ifndef TEAPACKET_TYPES_ARRAY_H
#define TEAPACKET_TYPES_ARRAY_H

#include "stddef.h"
#include "TeaPacket/Types/Numeric.h"

#include "TeaPacket/MacroUtils/Features.h"

#define TP_Array(Type) \
struct TP_##Type##Array{\
    Type* p;\
    size_t size;\
}

#define TP_ArrayView(Type) \
struct TP_##Type##ArrayView{\
const Type* p;\
size_t size;\
}

typedef TP_Array(char) TP_String;
typedef TP_Array(tp_byte) TP_ByteArray;

typedef TP_ArrayView(char) TP_StringView;
typedef TP_ArrayView(tp_byte) TP_ByteView;

TP_INLINE_FUNC TP_StringView TP_StrViewFromStr(const TP_String str) {
    TP_StringView view;
    view.p = str.p;
    view.size = str.size;
    return view;
}

TP_INLINE_FUNC TP_StringView TP_StrViewMake(const char* data, const size_t size) {
    TP_StringView view;
    view.p = data;
    view.size = size;
    return view;
}

#define TP_StrViewFromConstStr(msg) TP_StrViewMake(msg, sizeof(msg)-1)

#endif