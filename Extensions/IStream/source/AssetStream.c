#include "TeaPacket/Assets/Stream.h"
#include "TeaPacket/Extensions/IStream/IStream.h"
#include "TeaPacket/Assets/Assets.h"

static void AssetReadFunc(void* privData, const size_t amount, void* dest)
{
    TP_Assets_Stream_ReadBytes(privData, amount, dest);
}

static void AssetCloseFunc(void* privData)
{
    TP_Assets_Stream_Close(privData);
}

static void SeekFunc(void* privData, const ptrdiff_t amount, const TP_Assets_Stream_SeekBase seekBase)
{
    TP_Assets_Stream_Seek(privData, seekBase, amount);
}

static size_t TellFunc(void* privData)
{
    return TP_Assets_Stream_Tell(privData);
}

TP_Extension_IStream TP_Extensions_IStream_StreamFromAsset(TP_StringView assetPath)
{
    TP_Extension_IStream stream;
    stream.privData = TP_Assets_Stream_Open(assetPath);

    if (!stream.privData)
    {
        TP_Extension_IStream empty = {0};
        return empty;
    }
    stream.readFunc = AssetReadFunc;
    stream.closeFunc = AssetCloseFunc;
    stream.seekFunc = SeekFunc;
    stream.tellFunc = TellFunc;
    return stream;
}
