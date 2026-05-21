// ReSharper disable CppSomeObjectMembersMightNotBeInitialized
// ReSharper disable CppObjectMemberMightNotBeInitialized

/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/Assets/Assets.h"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

#include "TeaPacket/Logging/Logging.h"
#include "TeaPacket/Memory/Memory.h"


static constexpr auto assetPrepend = "assets/";

TP_String TP_Assets_ReadTextAsset(const TP_StringView assetPath)
{
    std::string assetSource(assetPrepend);
    assetSource.append(assetPath.p, assetPath.size);

    std::ifstream in(assetSource);
    if (!in.is_open())
    {
        TP_LogConstStr("Failed to open file!");
        return {nullptr, 0};
    }

    const size_t size = std::filesystem::file_size(assetSource);
    size_t truSize = 0;

    TP_String data{static_cast<char*>(TP_MemAlloc(size)), size};
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
        TP_LogConstStr("Failed to open file!");
        return {nullptr, 0};
    }

    const size_t size = std::filesystem::file_size(assetSource);

    const TP_ByteArray data{static_cast<tp_byte*>(TP_MemAlloc(size)), size};
    in.read(reinterpret_cast<char*>(data.p), static_cast<std::streamsize>(size));
    return data;
}
