#include <float.h>
#include <stdlib.h>
#include <string.h>

#include "TeaPacket/Logging/Logging.h"

const char testText[] = "Dynamic str";

int main(void)
{
    if (!TP_Logging_Init())
    {
        return -1;
    }

    TP_LogString(TP_StrViewFromConstStr("This should print right!"));

    {
        TP_String text;
        text.p = malloc(11);
        text.size = 11;
        memcpy(text.p, testText, text.size);
        TP_LogStringS(text);
        free(text.p);
    }

    TP_LogChar('z');


    TP_LogByte(0);
    TP_LogByte(0xFF);
    TP_LogByte(0x0A);
    TP_LogByte(0xFE);
    TP_LogByte(0x0F);

    TP_LogSLong(69420l);
    TP_LogSLong(-69420l);
    TP_LogSLong(1238913280l);
    TP_LogSLong(LONG_MAX);
    TP_LogSLong(LONG_MIN);

    TP_LogULong(3386395928ul);
    TP_LogULong(1);
    TP_LogULong(0);
    TP_LogULong(ULONG_MAX);

    TP_LogDouble(0.0);
    TP_LogDouble(1.02);
    TP_LogDouble(DBL_MAX);
    TP_LogDouble(-238.348);

    TP_LogBool(tp_false);
    TP_LogBool(tp_true);

    {
        char* data = malloc(11);
        memcpy(data, testText, 11);
        TP_LogCharN(data, 11);
        free(data);
    }



    TP_Logging_DeInit();
    return 0;
}