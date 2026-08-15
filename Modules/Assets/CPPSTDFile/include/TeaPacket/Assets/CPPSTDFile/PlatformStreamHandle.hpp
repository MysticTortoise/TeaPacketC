#pragma once

#include <fstream>
#include <string>


struct TP_Assets_StreamHandle
{
    std::ifstream stream;

    explicit TP_Assets_StreamHandle(const std::string& assetPath):
        stream(assetPath, std::ios::binary)
    {}
};