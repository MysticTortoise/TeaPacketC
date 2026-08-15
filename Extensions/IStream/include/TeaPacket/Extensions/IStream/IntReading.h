#ifndef TEAPACKET_EXTENSIONS_ISTREAM_INTREADING_H
#define TEAPACKET_EXTENSIONS_ISTREAM_INTREADING_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <string.h>

#include "TeaPacket/Endianness/Conversions.h"
#include "TeaPacket/Extensions/IStream/IStream.h"

#define ReadNumBigEndian(num) TP_INLINE_FUNC tp_u##num TP_Extension_IStream_Read##num##BigEndian(TP_Extension_IStream* stream) {\
    tp_u##num x; \
    TP_Extension_IStream_Read(stream, sizeof(x), &x);\
    x = TP_FromU##num##BigEndian(x); \
    return x; \
}
#define ReadNumLittleEndian(num) TP_INLINE_FUNC tp_u##num TP_Extension_IStream_Read##num##LittleEndian(TP_Extension_IStream* stream) {\
tp_u##num x; \
TP_Extension_IStream_Read(stream, sizeof(x), &x);\
x = TP_FromU##num##LittleEndian(x); \
return x; \
}

#define ReadNumEndian(num) ReadNumBigEndian(num) ReadNumLittleEndian(num)

ReadNumEndian(16)
ReadNumEndian(32)
ReadNumEndian(64)


#undef ReadNumBigEndian
#undef ReadNumLittleEndian
#undef ReadNumEndian
    
#ifdef __cplusplus
}
#endif
#endif
