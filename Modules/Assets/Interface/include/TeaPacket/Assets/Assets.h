/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

#ifndef TEAPACKET_ASSETS_H
#define TEAPACKET_ASSETS_H
#ifdef __cplusplus
extern "C"
{
#endif


#include "TeaPacket/Types/Array.h"

/**
 * @brief Reads a text asset via a path.
 * @param assetPath The path of the asset to read.
 * @return A TP_String containing the text read from the path. Should be freed via TP_Free().
 * @details The returned TP_String should have its ptr set to 0 if the asset failed to read.
 */
TP_String
TP_Assets_ReadTextAsset(TP_StringView assetPath);

/**
 * @brief Reads a binary asset via a path.
 * @param assetPath The path of the asset to read.
 * @return A TP_ByteArray containing the binary data read from the path. Should be freed via TP_Free().
 * @details The returned TP_ByteArray should have its ptr set to 0 if the asset failed to read.
 */
TP_ByteArray
TP_Assets_ReadBinaryAsset(TP_StringView assetPath);

#ifdef __cplusplus
}
#endif
#endif
