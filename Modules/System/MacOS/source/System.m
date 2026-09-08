/* Copyright (C) 2026 Kevin "MysticTortoise" Tessier */
#include "TeaPacket/System/System.h"

#import "Cocoa/Cocoa.h"

/* Thank you very much to both Cocoa With Love and GLFW, i learned from their code. */

static struct {
    id delegate;

    id menubar;
    id appMenuItem;

    id appMenu;
    id quitMenuItem;

    BOOL shouldQuit;
} sysContext;


@interface TPSystemMacOSDelegate : NSObject<NSApplicationDelegate>
@end

@implementation TPSystemMacOSDelegate
- (void)applicationDidFinishLaunching:(NSNotification *) notification
{
    [NSApp stop:nil];
}

- (NSApplicationTerminateReply) applicationShouldTerminate:(NSApplication *) sender
{
    sysContext.shouldQuit = YES;
    return NSTerminateCancel;
}
@end

tp_bool TP_System_Init(void){
    @autoreleasepool{
    sysContext.shouldQuit = NO;

    [NSApplication sharedApplication];

    sysContext.delegate = [[TPSystemMacOSDelegate alloc] init];
    [NSApp setDelegate:sysContext.delegate];

    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    sysContext.menubar = [NSMenu new];
    sysContext.appMenuItem = [NSMenuItem new];

    [sysContext.menubar addItem:sysContext.appMenuItem];
    [NSApp setMainMenu:sysContext.menubar];

    sysContext.appMenu = [NSMenu new];
    id appName = [[NSProcessInfo processInfo] processName];
    id quitTitle = [@"Quit " stringByAppendingString:appName];
    sysContext.quitMenuItem = [[NSMenuItem alloc] 
        initWithTitle:quitTitle
        action:@selector(terminate:)
        keyEquivalent:@"q"
    ];

    [sysContext.appMenu addItem:sysContext.quitMenuItem];
    [sysContext.appMenuItem setSubmenu:sysContext.appMenu];


    if(![[NSRunningApplication currentApplication] isFinishedLaunching]){
        [NSApp finishLaunching];
    }
    [NSApp activate];

}

    return tp_true;
}
void TP_System_DeInit(void) {
    [sysContext.menubar release];
    [sysContext.appMenuItem release];

    [sysContext.appMenu release];
    [sysContext.quitMenuItem release];

    [NSApp setDelegate:nil];
    [sysContext.delegate release];
    sysContext.delegate = nil;
}

void TP_System_Process(void)
{
    @autoreleasepool {
        while(1){
            NSEvent* event = [NSApp 
                nextEventMatchingMask:NSEventMaskAny
                untilDate:[NSDate distantPast]
                inMode:NSDefaultRunLoopMode
                dequeue:YES];
        
            if(event == nil)
                break;
        
            [NSApp sendEvent:event];
        }


    }
}

tp_bool TP_System_ShouldRun(void)
{
    return (tp_bool)(!sysContext.shouldQuit);
}

