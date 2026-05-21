/* ReSharper disable once CppMissingIncludeGuard */
/* ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile*/

/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains a number of default implementations for logging functions.
 * These only require that TP_LogString be implemented.
 * These are not required to use but speed up the process of making logging implementations drastically.
 */
#include <stdio.h>
#include <stdlib.h>

#include "TeaPacket/Logging/Logging.h"
#include "TeaPacket/Memory/Memory.h"

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


void TP_LogStringS(const TP_String str)
{
    TP_StringView strV;
    strV.p = str.p;
    strV.size = str.size;
    TP_LogString(strV);
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
    char text[6];
    str.p = text;
    str.size = 6;

    text[0] = '0';
    text[1] = 'x';
    snprintf(&text[2], 4, "%hX", b);

    TP_LogString(str);
}

void TP_LogSLong(const signed long x)
{
    TP_StringView str;
    char* text;

    size_t digits = numPlacesUL(labs(x));
    if (x < 0) {++digits;}
    text = (char*)TP_MemAlloc(digits+1);

    str.p = text;
    str.size = digits;

    snprintf(text, digits+1,"%ld", x);
    TP_LogString(str);
    free(text);
}

void TP_LogULong(const unsigned long x)
{
    TP_StringView str;
    char* text;

    const size_t digits = numPlacesUL(x);
    text = (char*)TP_MemAlloc(digits+1);

    str.p = text;
    str.size = digits;

    snprintf(text, digits+1,"%lu", x);
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

void TP_LogCharN(const char* c, const size_t n)
{
    TP_StringView strview;
    strview.p = c;
    strview.size = n;
    TP_LogString(strview);
}