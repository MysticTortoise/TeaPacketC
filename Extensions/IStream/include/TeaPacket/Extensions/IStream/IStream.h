#ifndef TEAPACKET_EXTENSIONS_ISTREAM_H
#define TEAPACKET_EXTENSIONS_ISTREAM_H
#include "TeaPacket/Assets/StreamSeekBase.h"
#include "TeaPacket/Types/Array.h"
#include "TeaPacket/MacroUtils/Features.h"


#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*TP_Ext_IStream_ReadFunc)(void* privData, size_t amount, void* dest);
typedef void (*TP_Ext_IStream_SeekFunc)(void* privData, ptrdiff_t amount, TP_Assets_Stream_SeekBase seekBase);
typedef void (*TP_Ext_IStream_CloseFunc)(void* privData);
typedef size_t (*TP_Ext_IStream_TellFunc)(void* privData);
    
typedef struct{
    TP_Ext_IStream_ReadFunc readFunc;
    TP_Ext_IStream_CloseFunc closeFunc;
    TP_Ext_IStream_SeekFunc seekFunc;
    TP_Ext_IStream_TellFunc tellFunc;
    void* privData;
} TP_Extension_IStream;

TP_Extension_IStream TP_Extensions_IStream_StreamFromAsset(TP_StringView assetPath);
TP_Extension_IStream TP_Extensions_IStream_StreamFromMemory(TP_ByteView memData);


TP_INLINE_FUNC void TP_Extension_IStream_Read(const TP_Extension_IStream* stream, const size_t amount, void* dest)
{
    stream->readFunc(stream->privData, amount, dest);
}
TP_INLINE_FUNC void TP_Extension_IStream_Close(const TP_Extension_IStream* stream)
{
    stream->closeFunc(stream->privData);
}

TP_INLINE_FUNC void TP_Extension_IStream_Skip(const TP_Extension_IStream* stream, const size_t amount)
{
    stream->seekFunc(stream->privData, (ptrdiff_t)amount, TP_Assets_Stream_SeekBase_Current);
}

TP_INLINE_FUNC void TP_Extension_IStream_Seek(const TP_Extension_IStream* stream, const ptrdiff_t amount, const TP_Assets_Stream_SeekBase seekBase)
{
    stream->seekFunc(stream->privData, amount, seekBase);
}

TP_INLINE_FUNC size_t TP_Extension_IStream_Tell(TP_Extension_IStream* stream)
{
    return stream->tellFunc(stream);
}

#ifdef __cplusplus
}
#endif

#endif