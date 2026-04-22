#include <assert.h>

#include "stdio.h"

#include "TeaPacket/Endianness/Endian.h"
#include "TeaPacket/Logging/Logging.h"
#include "TeaPacket/Input/Input.h"

int main(void)
{
    assert(TP_SwapU16(0x1234) == 0x3412);
    assert(TP_SwapU32(0x12345678) == 0x78563412);

    return 0;
}