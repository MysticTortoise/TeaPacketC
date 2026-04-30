
#include "TeaPacket/Bundled/Init.h"
#include "TeaPacket/Bundled/DeInit.h"

#include "TeaPacket/Assets/ReadAsset.h"
#include "TeaPacket/Memory/Memory.h"

#include "TeaPacket/TestUtil/String.h"
#include <assert.h>

int main(void)
{

    TP_Bundled_Init();

    {
        const TP_StringView file = TP_StrViewFromConstStr("test.txt");
        const TP_String text = TP_Assets_ReadTextAsset(file);
        assert(IsStringEqual(StrViewFromStr(text),  StrViewFromConstStr("Hello, World!\nLine TWO!")));
        TP_MemFree(text.p);
    }

    {
        const TP_StringView file = TP_StrViewFromConstStr("dir/test2.txt");
        const TP_String text = TP_Assets_ReadTextAsset(file);
        assert(IsStringEqual(StrViewFromStr(text),  StrViewFromConstStr("HIII!!")));
        TP_MemFree(text.p);
    }

    TP_Bundled_DeInit();

    return 0;
}
