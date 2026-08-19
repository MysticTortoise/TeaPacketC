/* ReSharper disable once CppMissingIncludeGuard */
/* ReSharper disable CppNonInlineFunctionDefinitionInHeaderFile*/

/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */

/* This file contains a number of default implementations for logging functions.
 * These only require that TP_LogString be implemented.
 * These are not required to use but speed up the process of making logging implementations drastically.
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "TeaPacket/Logging/Logging.h"
#include "TeaPacket/Memory/Memory.h"
#include "TeaPacket/MacroUtils/Features.h"

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

static const char HexList[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static void numToStr(unsigned long x, char* dest, const size_t digits)
{
    unsigned int i = (unsigned int)digits;
    while (1)
    {
        if (--i > digits)
            break;
        dest[i] = HexList[x % 10];
        x /= 10;
    }
    assert(x == 0);
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
    char text[4];
    str.p = text;
    str.size = 4;

    text[0] = '0';
    text[1] = 'x';
    text[2] = HexList[b >> 4 & 0x0F];
    text[3] = HexList[b & 0x0F];

    TP_LogString(str);
}

void TP_LogSLong(const signed long x)
{
    TP_StringView str;
    char* text;

    if (x >= 0)
    {
        TP_LogULong((unsigned long)x);
        return;
    }

    const size_t digits = numPlacesUL(labs(x)) + 1;
    text = (char*)TP_MemAlloc(digits);

    str.p = text;
    str.size = digits;

    text[0] = '-';
    numToStr(-x, &text[1], digits-1);

    TP_LogString(str);
    free(text);
}

void TP_LogULong(const unsigned long x)
{
    TP_StringView str;
    char* text;

    const size_t digits = numPlacesUL(x);
    text = (char*)TP_MemAlloc(digits);

    str.p = text;
    str.size = digits;

    numToStr(x, text, digits);
    TP_LogString(str);
    free(text);
}

void TP_LogDouble(const double x)
{

    TP_StringView str;
    char text[1024] = {0};
    str.p = text;
    str.size = 1024;

    /* Todo: make not shit, dont depend on snprintf?  */

#if  TP_C_VER >= TP_C_VER99
    snprintf(text,1024, "%f", x);
#elif defined(TP_HAS_MSC)
    sprintf_s(text,1024, "%f", x);
#else
    sprintf(text,"%f", x);
#endif

    str.size = strlen(str.p);

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