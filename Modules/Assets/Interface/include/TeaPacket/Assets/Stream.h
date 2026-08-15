/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#ifndef TEAPACKET_ASSETS_STREAM_H
#define TEAPACKET_ASSETS_STREAM_H

#include "TeaPacket/Assets/StreamSeekBase.h"
#include "TeaPacket/Types/Array.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct TP_Assets_StreamHandle TP_Assets_StreamHandle;

TP_Assets_StreamHandle* TP_Assets_Stream_Open(TP_StringView assetPath);

void TP_Assets_Stream_Close(TP_Assets_StreamHandle* handle);

void TP_Assets_Stream_ReadBytes(TP_Assets_StreamHandle* handle, size_t amount, void* dest);

void TP_Assets_Stream_Seek(TP_Assets_StreamHandle* handle, TP_Assets_Stream_SeekBase seekBase, ptrdiff_t offsetFromBase);

void TP_Assets_Stream_Skip(TP_Assets_StreamHandle* handle, size_t amount);

size_t TP_Assets_Stream_Tell(TP_Assets_StreamHandle* handle);

#ifdef __cplusplus
}
#endif
#endif