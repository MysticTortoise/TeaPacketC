#ifndef TEAPACKET_TESTPROGRAMS_GRAPHICS_TESTS_H
#define TEAPACKET_TESTPROGRAMS_GRAPHICS_TESTS_H
#include "TeaPacket/Types/Numeric.h"

typedef enum
{
    GfxTests_Boot = 0,
    GfxTests_CreateDisplays = 1,
    GfxTests_PresentDisplays = 2,
    GfxTests_ClearColor = 3,
    GfxTests_Shaders_Mesh = 4,
    GfxTests_Textures = 5,
    GfxTests_ShaderBuffers = 6,
    GfxTests_MAX
} GfxTestID;

typedef struct
{
    tp_bool (*initFunc)(void);
    void (*renderFunc)(void);
    void (*deInitFunc)(void);
} GfxTest;

extern GfxTest BootTest;
extern GfxTest CreateDisplayTest;
extern GfxTest PresentDisplayTest;
extern GfxTest ClearColorTest;
extern GfxTest ShadersMeshTest;
extern GfxTest TextureTest;
extern GfxTest ShaderBufferTest;

#define GFXTEST_COUNT (GFXTESTS_ALLOWED < GfxTests_MAX) ? GFXTESTS_ALLOWED : GfxTests_MAX;


#endif
