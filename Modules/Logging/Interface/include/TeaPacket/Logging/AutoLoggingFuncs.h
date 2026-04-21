/* ReSharper disable once CppMissingIncludeGuard */
/* ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile*/
#include <stdio.h>
#include <stdlib.h>

#include "TeaPacket/Logging/Logging.h"

static size_t numPlacesUL(unsigned long x)
{
    int r = 1;
    while (x > 9)
    {
        x /= 10;
        r++;
    }
    return r;
}

void TP_LogChar(const char c)
{
    TP_StringView str;
    str.p = &c;
    str.size = 1;
    TP_LogString(str);
}

void TP_LogByte(const tp_byte b)
{
    TP_StringView str;
    char text[4];
    str.p = text;
    str.size = 4;

    text[0] = '0';
    text[1] = 'x';
    snprintf(&text[2], 2, "%hX", b);

    TP_LogString(str);
}

void TP_LogSLong(const signed long x)
{
    TP_StringView str;
    char* text;

    size_t digits = numPlacesUL(labs(x));
    if (x < 0) {++digits;}
    text = (char*)malloc(digits);

    str.p = text;
    str.size = 4;

    snprintf(text, digits,"%ld", x);
    TP_LogString(str);
    free(text);
}

void TP_LogULong(const unsigned long x)
{
    TP_StringView str;
    char* text;

    const size_t digits = numPlacesUL(x);
    text = (char*)malloc(digits);

    str.p = text;
    str.size = 4;

    snprintf(text, digits,"%lu", x);
    TP_LogString(str);
    free(text);
}

void TP_LogDouble(const double x)
{
    TP_StringView str;
    char text[64] = {0};
    str.p = text;
    str.size = 64;

    snprintf(text, 64,"%f", x);
    TP_LogString(str);
}

void TP_LogBool(const tp_bool x)
{
    if (x)
    {
        const TP_StringView data = {"true", 4};
        TP_LogString(data);
    } else
    {
        const TP_StringView data = {"false", 5};
        TP_LogString(data);
    }
}