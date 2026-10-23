#include "TeaPacket/Graphics/GS/GL/gl.h"
#include "TeaPacket/Graphics/GS/GL/GLAD.h"

#include "TeaPacket/Types/Numeric.h"

tp_bool TP_GfxGS_GL_GLADInit(void)
{
    if (!gladLoaderLoadGL())
    {
        return tp_false;
    }
    return tp_true;
}
void TP_GfxGS_GL_GLADDeInit(void)
{
    gladLoaderUnloadGL();
}
