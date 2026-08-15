#include "TeaPacket/Assets/Stream.h"
#include <fstream>

#include "General.hpp"
#include "TeaPacket/Assets/CPPSTDFile/PlatformStreamHandle.hpp"

using namespace TeaPacket::Assets::CPPSTDFile;

TP_Assets_StreamHandle* TP_Assets_Stream_Open(TP_StringView assetPath)
{
    auto* streamHandle = new TP_Assets_StreamHandle(GetFilePath(assetPath));
    
    if (!streamHandle->stream.is_open())
    {
        return nullptr;
    }

    return streamHandle;
}


void TP_Assets_Stream_Close(TP_Assets_StreamHandle* handle)
{
    handle->stream.close();
    delete handle;
}

void TP_Assets_Stream_ReadBytes(TP_Assets_StreamHandle* handle, const size_t amount, void* dest)
{
    size_t a = handle->stream.tellg();
    (void)a;
    handle->stream.read(static_cast<char*>(dest), static_cast<std::streamsize>(amount));
}

void TP_Assets_Stream_Seek(TP_Assets_StreamHandle* handle, const TP_Assets_Stream_SeekBase seekBase, const ptrdiff_t offsetFromBase)
{
    std::ifstream::seekdir base;
    switch (seekBase)
    {
    case TP_Assets_Stream_SeekBase_Begin:
        base = std::ios_base::beg;
        break;
    case TP_Assets_Stream_SeekBase_End:
        base = std::ios_base::end;
        break;
    case TP_Assets_Stream_SeekBase_Current:
        base = std::ios_base::cur;
        break;
    default: return;
    }

    handle->stream.seekg(offsetFromBase, base);
}

void TP_Assets_Stream_Skip(TP_Assets_StreamHandle* handle, const size_t amount)
{
    size_t a = handle->stream.tellg();
    (void)a;
    handle->stream.ignore(static_cast<std::streamsize>(amount));
}

size_t TP_Assets_Stream_Tell(TP_Assets_StreamHandle* handle)
{
    return handle->stream.tellg();
}
