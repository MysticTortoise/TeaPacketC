#ifndef TEAPACKET_TYPES_ARRAY_H
#define TEAPACKET_TYPES_ARRAY_H

#include "stddef.h"
#include "TeaPacket/Types/Numeric.h"

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

#endif