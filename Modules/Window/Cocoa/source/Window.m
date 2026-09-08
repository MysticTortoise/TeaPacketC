#include "TeaPacket/Window/Window.h"

#include "TeaPacket/Window/PlatformWindow.h"
#include <stdlib.h>

#include "TeaPacket/Memory/Memory.h"

#import "Cocoa/Cocoa.h"

static NSMutableArray<NSValue*>* winArray = nil;

TP_Window* TP_Window_Create(const TP_Window_Params* params){
    if(winArray == nil){
        winArray = [NSMutableArray array];
    }

    TP_Window* window = calloc(1, sizeof(TP_Window));
    id cWin = [[NSWindow alloc]
        initWithContentRect:NSMakeRect(0,0, params->width, params->height)
        styleMask: NSWindowStyleMaskTitled |
                        NSWindowStyleMaskClosable |
                        NSWindowStyleMaskMiniaturizable |
                        NSWindowStyleMaskResizable
        backing: NSBackingStoreBuffered
        defer: NO
    ];
    [cWin cascadeTopLeftFromPoint: NSMakePoint(params->x, params->y)];
    window->window = cWin;
    //TP_Window_SetTitle(window, params->title);
    
    [cWin makeKeyAndOrderFront:nil];

    [winArray addObject:[NSValue valueWithPointer:window]];

    [NSApp activateIgnoringOtherApps:YES];

    return window;
}

void TP_Window_Destroy(TP_Window* window){
    for (NSValue *v in winArray) {
        if ([v pointerValue] == window) {
            [winArray removeObject:v];
            break;
        }
    }

    [window->window release];
    free(window);
} 

void TP_Window_ProcessEvents(TP_Window* w){
    (void)w;
}

tp_u16 TP_Window_GetXPos(TP_Window* window)
{
    return (tp_u16)([window->window frame].origin.x);
}

tp_u16 TP_Window_GetYPos(TP_Window* window)
{
    CGFloat screenHeight = [[NSScreen mainScreen] frame].size.height;
    NSRect localFrame = [window->window frame];
    CGFloat yFromTopLeft = screenHeight - (localFrame.origin.y + localFrame.size.height);
    return (tp_u16)yFromTopLeft;
}

tp_u16 TP_Window_GetWidth(TP_Window* window)
{
    return (tp_u16)([window->window frame].size.width);
}

tp_u16 TP_Window_GetHeight(TP_Window* window)
{
    return (tp_u16)([window->window frame].size.height);
}

TP_String TP_Window_GetTitle(TP_Window* window)
{
    NSString* winTitle = [window->window title];
    size_t length = [winTitle lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    char* text = (char*)TP_MemAlloc(length);
    memcpy(text, [winTitle UTF8String], length);

    TP_String s;
    s.p = text;
    s.size = length;

    return s;
}

void TP_Window_SetXPos(TP_Window* window, const tp_u16 xPos)
{
    CGPoint p = [window->window frame].origin;
    p.x = xPos;
    [window->window setFrameOrigin:p];
}

void TP_Window_SetYPos(TP_Window* window, const tp_u16 yPos)
{
    [window->window cascadeTopLeftFromPoint: NSMakePoint([window->window frame].origin.x, yPos)];
}

void TP_Window_SetWidth(TP_Window* window, const tp_u16 width)
{
    [window->window setContentSize:NSMakeSize(width, [window->window frame].size.height)];
}

void TP_Window_SetHeight(TP_Window* window, const tp_u16 height)
{
    [window->window setContentSize:NSMakeSize([window->window frame].size.width, height)];
}

void TP_Window_SetTitle(TP_Window* window, const TP_StringView name)
{
    NSString* string = [[NSString alloc] 
        initWithBytesNoCopy: (void*)name.p
        length: name.size
        encoding: NSUTF8StringEncoding
        freeWhenDone: NO
    ];

    [window->window setTitle:string];
    [string release];
}

size_t TP_Window_GetCount(void)
{
    return [winArray count];
}

TP_Window* TP_Window_Get(const size_t index)
{
    return [[winArray objectAtIndex:index] pointerValue];
}

tp_u16 TP_Window_GetID(const TP_Window* window)
{
    for (size_t i = 0; i < [winArray count]; ++i)
    {
        if (window == [[winArray objectAtIndex:i] pointerValue])
            return (tp_u16)i;
    }
    return TP_MAXU16;
}

TP_Window* TP_Window_GetActive(void)
{
    NSWindow* win = [[NSApplication sharedApplication] mainWindow];
    for (NSValue *v in winArray) {
        TP_Window* vWin = (TP_Window*)[v pointerValue];
        if (vWin->window == win) {
            return vWin;
            break;
        }
    }
    return (TP_Window*)([[winArray objectAtIndex:0] pointerValue]);
}


