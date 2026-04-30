// ReSharper disable CppSomeObjectMembersMightNotBeInitialized
// ReSharper disable CppObjectMemberMightNotBeInitialized
#include "TeaPacket/Assets/ReadAsset.h"

#include <cassert>

#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/Logging/Logging.h"

#include <string>
#include <fstream>
#include <filesystem>

static constexpr auto assetPrepend = "/vol/content/";

TP_String TP_Assets_ReadTextAsset(const TP_StringView assetPath)
{
    std::string assetSource(assetPrepend);
    assetSource.append(assetPath.p, assetPath.size);

    std::ifstream in(assetSource);
    if (!in.is_open())
    {
        TP_LogConstStr("Failed to open file!");
        return {nullptr, 0};
        //throw std::runtime_error(assetSource + " does not exist!");
    }

    const auto size = std::filesystem::file_size(assetSource);
    size_t truSize = 0;

    TP_String data {static_cast<char*>(TP_MemAlloc(size)), size};
    char* ptr = data.p;
    char c;
    while ((in.get(c), !in.eof()))
    {
        truSize++;
        *ptr = c;
        ptr++;
    }
    assert(truSize <= size);
    data.p = static_cast<char*>(TP_ReAlloc(data.p, truSize));
    data.size = truSize;
    return data;
}

TP_ByteArray TP_Assets_ReadBinaryAsset(const TP_StringView assetPath)
{
    std::string assetSource(assetPrepend);
    assetSource.append(assetPath.p, assetPath.size);

    std::ifstream in(assetSource, std::ios::binary);
    if (!in.is_open())
    {
        return {nullptr, 0};
        //throw std::runtime_error(assetSource + " does not exist!");
    }

    const auto size = std::filesystem::file_size(assetSource);

    const TP_ByteArray data {static_cast<tp_byte*>(TP_MemAlloc(size)), size};
    in.read(reinterpret_cast<char*>(data.p), static_cast<std::streamsize>(size));
    return data;
}
