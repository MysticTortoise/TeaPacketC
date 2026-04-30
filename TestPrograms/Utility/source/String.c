#include "TeaPacket/TestUtil/String.h"


#include <string.h>

tp_bool IsStringEqual(const TP_StringView a, const TP_StringView b)
{
    if (a.size != b.size)
        return tp_false;

    for (size_t i = 0; i < a.size; i++)
    {
        if (a.p[i] != b.p[i])
            return tp_false;
    }

    return tp_true;
}

TP_StringView StrViewFromStr(const TP_String str)
{
    TP_StringView v;
    v.p = str.p;
    v.size = str.size;
    return v;
}

TP_StringView StrViewFromConstStr(const char* msg)
{
    TP_StringView v;
    v.p = msg;
    v.size = strlen(msg);
    return v;
}
