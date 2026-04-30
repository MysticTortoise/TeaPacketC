
#ifndef TEAPACKET_LOGGING_H
#define TEAPACKET_LOGGING_H
#ifdef __cplusplus
extern "C" {
#endif

#include "TeaPacket/Types/Array.h"
#include "TeaPacket/Types/Numeric.h"

tp_bool TP_Logging_Init(void);
void TP_Logging_DeInit(void);

void TP_LogString(TP_StringView);
void TP_LogStringS(TP_String);
void TP_LogChar(char);
void TP_LogByte(tp_byte);
void TP_LogSLong(  signed long);
void TP_LogULong(unsigned long);
void TP_LogDouble(double);
void TP_LogBool(tp_bool);
void TP_LogCharN(const char*, size_t);

#define TP_LogConstStr(msg) TP_LogCharN(msg, sizeof(msg)-1)


#ifdef __cplusplus
}
#endif
#endif
