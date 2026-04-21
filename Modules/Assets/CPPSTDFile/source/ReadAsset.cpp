// ReSharper disable CppSomeObjectMembersMightNotBeInitialized
// ReSharper disable CppObjectMemberMightNotBeInitialized
#include "TeaPacket/Assets/ReadAsset.h"

#include <string>
#include <fstream>

static constexpr auto assetPrepend = "assets/";

TP_String TP_Assets_ReadTextAsset(const TP_String assetPath)
{
    std::string assetSource(assetPrepend);
    assetSource.append(assetPath.p, assetPath.size);

    std::ifstream in(assetSource);
    if (!in.is_open())
    {
        return {nullptr, 0};
        //throw std::runtime_error(assetSource + " does not exist!");
    }

    in.seekg(0, std::ios::end);
    const size_t size = in.tellg();
    in.seekg(0);

    const TP_String data {nullptr, size};
    in.read(data.p, static_cast<std::streamsize>(size));
    return data;
}

TP_ByteArray TP_Assets_ReadBinaryAsset(TP_String assetPath)
{
    std::string assetSource(assetPrepend);
    assetSource.append(assetPath.p, assetPath.size);

    std::ifstream in(assetSource, std::ios::binary);
    if (!in.is_open())
    {
        return {nullptr, 0};
        //throw std::runtime_error(assetSource + " does not exist!");
    }

    in.seekg(0, std::ios::end);
    const size_t size = in.tellg();
    in.seekg(0);

    const TP_ByteArray data {nullptr, size};
    in.read(reinterpret_cast<char*>(data.p), static_cast<std::streamsize>(size));
    return data;
}
