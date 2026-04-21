#ifndef TEAPACKET_ASSETS_READASSET_H
#define TEAPACKET_ASSETS_READASSET_H
#ifdef __cplusplus
extern "C" {
#endif


#include "TeaPacket/Types/Array.h"

TP_String
TP_Assets_ReadTextAsset(TP_String assetPath);

TP_ByteArray
TP_Assets_ReadBinaryAsset(TP_String assetPath);

#ifdef __cplusplus
}
#endif
#endif