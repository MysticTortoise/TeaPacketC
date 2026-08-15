#include <string.h>

#include "TeaPacket/Extensions/IStream/IStream.h"

#include "stdlib.h"
#include "../../../Modules/Memory/Interface/include/TeaPacket/Memory/Memory.h"

typedef struct
{
    const tp_byte* data;
    const tp_byte* start;
    const tp_byte* end;
} MemoryStream;

static void ReadFunc(void* privData, const size_t amount, void* dest)
{
    MemoryStream* stream = privData;
    memcpy(dest, stream->data, amount);
    stream->data += amount;
}

static void CloseFunc(void* privData)
{
    TP_MemFree(privData);
}

static void SeekFunc(void* privData, const ptrdiff_t amount, const TP_Assets_Stream_SeekBase seekBase)
{
    MemoryStream* stream = privData;
    switch (seekBase)
    {
    case TP_Assets_Stream_SeekBase_Begin:
        stream->data = stream->start + amount;
        return;
    case TP_Assets_Stream_SeekBase_End:
        stream->data = stream->end + amount;
        return;
    case TP_Assets_Stream_SeekBase_Current:
        stream->data += amount;
        return;
    }

}

static size_t TellFunc(void* privData)
{
    const MemoryStream* stream = privData;
    return stream->data - stream->start;
}

TP_Extension_IStream TP_Extensions_IStream_StreamFromMemory(TP_ByteView memData)
{
    MemoryStream* data = TP_MemAlloc(sizeof(MemoryStream));
    TP_Extension_IStream stream;
    
    data->data = memData.p;
    data->start = memData.p;
    data->end = memData.p + memData.size;
    
    stream.privData = data;
    stream.readFunc = ReadFunc;
    stream.closeFunc = CloseFunc;
    stream.seekFunc = SeekFunc;
    stream.tellFunc = TellFunc;
    return stream;
}
