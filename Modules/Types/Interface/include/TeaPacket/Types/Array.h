/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains array based types.
 * The TP_Array and TP_ArrayView macros can be used to generate array types for different subtypes.
 **/
#ifndef TEAPACKET_TYPES_ARRAY_H
#define TEAPACKET_TYPES_ARRAY_H

#include "stddef.h"
#include "TeaPacket/Types/Numeric.h"

#include "TeaPacket/MacroUtils/Features.h"

/**
 * The TP_Array base type represents a modifiable array with a size.
 * This should be used instead of separating the array with a pointer and a size.
 *
 * Any public TP_Array types should be allocated with TP_MemAlloc and freed with TP_MemFree.
 **/
#define TP_Array(Type) \
struct TP_##Type##Array{\
    Type* p;\
    size_t size;\
}

/**
 * The TP_ArrayView base type represents a non-modifiable view of data with a size.
 * This should be used to send data to functions that will not modify it.
 **/
#define TP_ArrayView(Type) \
struct TP_##Type##ArrayView{\
const Type* p;\
size_t size;\
}

/**
 * Represents a String, with a size. Should always be used instead of C Strings in TeaPacket.
 */
typedef TP_Array(char) TP_String;
typedef TP_Array(tp_byte) TP_ByteArray;

/**
 * Represents a view of a String, with a size. Should always be used similar to C++'s std::string_view.
 */
typedef TP_ArrayView(char) TP_StringView;
typedef TP_ArrayView(tp_byte) TP_ByteView;


/**
 * Creates a TP_StringView from a TP_String.
 * @param str The string to create a TP_StringView of.
 * @return The created TP_StringView.
 */
TP_INLINE_FUNC TP_StringView TP_StrViewFromStr(const TP_String str) {
    TP_StringView view;
    view.p = str.p;
    view.size = str.size;
    return view;
}

/**
 * Creates a TP_StringView from a source pointer and a size.
 * @param data A pointer to the source data to view.
 * @param size The size of the source data to view.
 * @return The created TP_StringView.
 */
TP_INLINE_FUNC TP_StringView TP_StrViewMake(const char* data, const size_t size) {
    TP_StringView view;
    view.p = data;
    view.size = size;
    return view;
}

/**
 * Creates a StringView from an inline string literal.
 * @param msg The constant message to create a StringView for.
 */
#define TP_StrViewFromConstStr(msg) TP_StrViewMake(msg, sizeof(msg)-1)

/**
 * Creates a StringView brace init list from an inline string literal.
 * @param msg The constant message to create a StringView for.
 */
#define TP_StrViewFromConstStrBrace(msg) {msg, sizeof(msg)-1}

#endif