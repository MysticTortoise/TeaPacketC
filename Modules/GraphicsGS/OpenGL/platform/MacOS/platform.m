#include "TeaPacket/Graphics/GS/GL/GLAD.h"

#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>

#include "TeaPacket/Graphics/GS/Display.h"

#include "TeaPacket/Window/Window.h"
#include "TeaPacket/Window/PlatformWindow.h"


struct GLDisplayMac
{
    NSOpenGLView* glView;
};
static __unsafe_unretained NSOpenGLContext* context = nil;
static __unsafe_unretained NSMutableArray<NSValue*>* dispArray = nil;
static __unsafe_unretained NSOpenGLPixelFormat* pixelFormat = nil;

// ReSharper disable once CppUseInternalLinkage
tp_bool TP_GraphicsGS_Init(void)
{
    NSOpenGLPixelFormatAttribute attribs[] = {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 24,
        0
    };

    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];
    if(!pixelFormat)
    {
        return tp_false;
    }

    context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    if(!context)
    {
        return tp_false;
    }

    [context makeCurrentContext];


    if (!TP_GfxGS_GL_GLADInit())
    {
        return tp_false;
    }

    dispArray = [NSMutableArray array];


    return tp_true;
}

// ReSharper disable once CppUseInternalLinkage
void TP_GraphicsGS_DeInit(void)
{
    if(pixelFormat)
    {
        [pixelFormat release];
        pixelFormat = nil;
    }
    if(context)
    {
        [context release];
        context = nil;
    }
    if(dispArray)
    {
        [dispArray release];
        dispArray = nil;
    }

}

void TP_GfxGS_GL_CreateWindow(TP_GfxGS_DisplayParams params)
{
    TP_Window_Params winParams;
    winParams.x = 0;
    winParams.y = 0;

    winParams.width  = params.width;
    winParams.height = params.height;

    TP_Window* window = TP_Window_Create(&winParams);


    NSRect frame = NSMakeRect(0,0, params.width, params.height);
    struct GLDisplayMac* macDisplay = calloc(1, sizeof(struct GLDisplayMac));
    macDisplay->glView = [[NSOpenGLView alloc]
        initWithFrame:frame
        pixelFormat:pixelFormat];

    [window->window setContentView:macDisplay->glView];

    [dispArray addObject:[NSValue valueWithPointer:macDisplay]];
}

void TP_GfxGS_Display_BeginRender(const TP_GfxGS_DisplayID id)
{
    struct GLDisplayMac* disp = [[dispArray objectAtIndex:id] pointerValue];
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    [context setView:disp->glView];
#pragma clang diagnostic pop
    [context makeCurrentContext];
}

void TP_GfxGS_Display_FinishRender(void)
{
    [context flushBuffer];
}

void TP_GfxGS_Display_PresentAll(tp_bool waitForVSync)
{
    (void)waitForVSync;
}