/* The Mac side of a recompiled game (shell.h): AppKit for the window and the input, Core
 * Animation for the picture, the GameController framework for pads and Core Audio for sound. */
#import <Cocoa/Cocoa.h>
#import <GameController/GameController.h>
#import <QuartzCore/QuartzCore.h>

#include <AudioToolbox/AudioToolbox.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "data.h"
#include "shell.h"

static ShellOptions options;
static char folder[1024];

uint64_t shell_microseconds(void)
{
    return clock_gettime_nsec_np(CLOCK_UPTIME_RAW) / 1000u;
}

/* --- log ----------------------------------------------------------------------------------- */

static FILE *log_file;
static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

void shell_log_open(const char *name)
{
    char path[1200];
    snprintf(path, sizeof path, "%s/%s", folder, name);
    log_file = fopen(path, "w");
}

void shell_log(const char *line)
{
    pthread_mutex_lock(&log_lock);
    fprintf(stderr, "%s\n", line);
    if (log_file)
    {
        fprintf(log_file, "%s\n", line);
        fflush(log_file);
    }
    pthread_mutex_unlock(&log_lock);
}

static void show_error(NSString *message)
{
    NSAlert *alert = [[NSAlert alloc] init];
    alert.messageText = [NSString stringWithFormat:@"%s stopped.", options.game->title];
    alert.informativeText = message;
    alert.alertStyle = NSAlertStyleCritical;
    [alert runModal];
}

_Noreturn void shell_fatal(const char *message)
{
    char line[1200];
    snprintf(line, sizeof line, "FATAL: %s", message);
    shell_log(line);
    NSString *text = @(message);
    if (NSThread.isMainThread)
    {
        show_error(text);
    }
    else
    {
        dispatch_sync(dispatch_get_main_queue(), ^{
          show_error(text);
        });
    }
    exit(2);
}

/* --- frames -------------------------------------------------------------------------------- */

static pthread_mutex_t frame_lock = PTHREAD_MUTEX_INITIALIZER;
static uint32_t *frame_pixels;
static unsigned frame_width, frame_height;
static int frame_new;
static void (*refresh_hook)(void);

void shell_present(const uint32_t *pixels, unsigned width, unsigned height)
{
    pthread_mutex_lock(&frame_lock);
    if (width != frame_width || height != frame_height || !frame_pixels)
    {
        free(frame_pixels);
        frame_pixels = malloc((size_t)width * height * 4u);
        frame_width = width;
        frame_height = height;
    }
    if (frame_pixels)
    {
        memcpy(frame_pixels, pixels, (size_t)width * height * 4u);
        frame_new = 1;
    }
    pthread_mutex_unlock(&frame_lock);
}

void shell_set_refresh(void (*refresh)(void))
{
    refresh_hook = refresh;
}

void shell_wait_frame(void)
{
    static uint64_t next; /* nanoseconds */
    const uint64_t period = 1000000000u / 60u;
    const uint64_t now = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
    if (next == 0 || now > next + 4 * period)
    {
        next = now; /* late by frames (a pause, a slow load): start again from now */
    }
    next += period;
    if (next > now)
    {
        const uint64_t wait = next - now;
        const struct timespec ts = {(time_t)(wait / 1000000000u), (long)(wait % 1000000000u)};
        nanosleep(&ts, NULL);
    }
}

/* --- input --------------------------------------------------------------------------------- */

enum
{
    QUEUE = 512
};
static ShellInput queue[QUEUE];
static unsigned queue_head, queue_tail;
static pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
static _Atomic int pointer_x, pointer_y, pointer_inside;
static _Atomic uint32_t pads[2];
static _Atomic int quit_asked;
static uint64_t quit_time;

static void push_input(int kind, unsigned code, int down, int repeat)
{
    pthread_mutex_lock(&queue_lock);
    if (queue_tail - queue_head < QUEUE)
    {
        queue[queue_tail % QUEUE] = (ShellInput){kind, code, down, repeat};
        ++queue_tail;
    }
    pthread_mutex_unlock(&queue_lock);
}

int shell_input(ShellInput *input)
{
    int got = 0;
    pthread_mutex_lock(&queue_lock);
    if (queue_head != queue_tail)
    {
        *input = queue[queue_head % QUEUE];
        ++queue_head;
        got = 1;
    }
    pthread_mutex_unlock(&queue_lock);
    return got;
}

int shell_pointer(int *x, int *y)
{
    *x = pointer_x;
    *y = pointer_y;
    return pointer_inside;
}

uint32_t shell_pad(unsigned player)
{
    return player < 2 ? pads[player] : 0;
}

int shell_quit_requested(void)
{
    return quit_asked;
}

static void ask_quit(void)
{
    if (!quit_asked)
    {
        quit_time = shell_microseconds();
        quit_asked = 1;
        shell_log("the player closed the game");
    }
}

/* macOS virtual key codes (Carbon's kVK_*) to set 1 scan codes, 0x100 for the E0 prefix. */
static const uint16_t scan_codes[128] = {
    [0x00] = 0x1e,  [0x01] = 0x1f,  [0x02] = 0x20,  [0x03] = 0x21,  [0x04] = 0x23,  [0x05] = 0x22,
    [0x06] = 0x2c,  [0x07] = 0x2d,  [0x08] = 0x2e,  [0x09] = 0x2f,  [0x0a] = 0x56,  [0x0b] = 0x30,
    [0x0c] = 0x10,  [0x0d] = 0x11,  [0x0e] = 0x12,  [0x0f] = 0x13,  [0x10] = 0x15,  [0x11] = 0x14,
    [0x12] = 0x02,  [0x13] = 0x03,  [0x14] = 0x04,  [0x15] = 0x05,  [0x16] = 0x07,  [0x17] = 0x06,
    [0x18] = 0x0d,  [0x19] = 0x0a,  [0x1a] = 0x08,  [0x1b] = 0x0c,  [0x1c] = 0x09,  [0x1d] = 0x0b,
    [0x1e] = 0x1b,  [0x1f] = 0x18,  [0x20] = 0x16,  [0x21] = 0x1a,  [0x22] = 0x17,  [0x23] = 0x19,
    [0x24] = 0x1c,  [0x25] = 0x26,  [0x26] = 0x24,  [0x27] = 0x28,  [0x28] = 0x25,  [0x29] = 0x27,
    [0x2a] = 0x2b,  [0x2b] = 0x33,  [0x2c] = 0x35,  [0x2d] = 0x31,  [0x2e] = 0x32,  [0x2f] = 0x34,
    [0x30] = 0x0f,  [0x31] = 0x39,  [0x32] = 0x29,  [0x33] = 0x0e,  [0x35] = 0x01,  [0x38] = 0x2a,
    [0x39] = 0x3a,  [0x3a] = 0x38,  [0x3b] = 0x1d,  [0x3c] = 0x36,  [0x3d] = 0x138, [0x3e] = 0x11d,
    [0x41] = 0x53,  [0x43] = 0x37,  [0x45] = 0x4e,  [0x47] = 0x45,  [0x4b] = 0x135, [0x4c] = 0x11c,
    [0x4e] = 0x4a,  [0x52] = 0x52,  [0x53] = 0x4f,  [0x54] = 0x50,  [0x55] = 0x51,  [0x56] = 0x4b,
    [0x57] = 0x4c,  [0x58] = 0x4d,  [0x59] = 0x47,  [0x5b] = 0x48,  [0x5c] = 0x49,  [0x60] = 0x3f,
    [0x61] = 0x40,  [0x62] = 0x41,  [0x63] = 0x3d,  [0x64] = 0x42,  [0x65] = 0x43,  [0x67] = 0x57,
    [0x6d] = 0x44,  [0x6f] = 0x58,  [0x72] = 0x152, [0x73] = 0x147, [0x74] = 0x149, [0x75] = 0x153,
    [0x76] = 0x3e,  [0x77] = 0x14f, [0x78] = 0x3c,  [0x79] = 0x151, [0x7a] = 0x3b,  [0x7b] = 0x14b,
    [0x7c] = 0x14d, [0x7d] = 0x150, [0x7e] = 0x148};

/* The modifier keys and their device-dependent flag bits (IOLLEvent.h's NX_DEVICE*KEYMASK). */
static const struct
{
    uint16_t key;
    uint32_t mask;
} modifiers[] = {{0x38, 0x0002}, {0x3c, 0x0004}, {0x3b, 0x0001},
                 {0x3e, 0x2000}, {0x3a, 0x0020}, {0x3d, 0x0040}};

static uint8_t held[128];

static void key(unsigned mac_key, int down, int repeat)
{
    if (mac_key >= 128 || !scan_codes[mac_key])
    {
        return;
    }
    if (!down && !held[mac_key])
    {
        return;
    }
    held[mac_key] = (uint8_t)down;
    push_input(SHELL_KEY, scan_codes[mac_key], down, repeat);
}

static uint8_t buttons_held[3];

static void button(unsigned which, int down)
{
    if (which < 3 && buttons_held[which] != down)
    {
        buttons_held[which] = (uint8_t)down;
        push_input(SHELL_BUTTON, which, down, 0);
    }
}

/* The window lost the keyboard: everything held comes up. */
static void release_all(void)
{
    for (unsigned k = 0; k < 128; ++k)
    {
        if (held[k])
        {
            key(k, 0, 0);
        }
    }
    for (unsigned b = 0; b < 3; ++b)
    {
        button(b, 0);
    }
}

static uint32_t read_pad(GCController *controller)
{
    GCExtendedGamepad *g = controller.extendedGamepad;
    if (!g)
    {
        return 0;
    }
    uint32_t bits = 0;
    const float x = g.leftThumbstick.xAxis.value, y = g.leftThumbstick.yAxis.value;
    bits |= g.dpad.up.pressed || y > 0.5f ? SHELL_PAD_UP : 0;
    bits |= g.dpad.down.pressed || y < -0.5f ? SHELL_PAD_DOWN : 0;
    bits |= g.dpad.left.pressed || x < -0.5f ? SHELL_PAD_LEFT : 0;
    bits |= g.dpad.right.pressed || x > 0.5f ? SHELL_PAD_RIGHT : 0;
    bits |= g.buttonA.pressed ? SHELL_PAD_A : 0;
    bits |= g.buttonB.pressed ? SHELL_PAD_B : 0;
    bits |= g.buttonX.pressed ? SHELL_PAD_X : 0;
    bits |= g.buttonY.pressed ? SHELL_PAD_Y : 0;
    bits |= g.buttonMenu.pressed ? SHELL_PAD_MENU : 0;
    bits |= g.buttonOptions.pressed ? SHELL_PAD_OPTIONS : 0;
    bits |= g.leftShoulder.pressed ? SHELL_PAD_SHOULDER_L : 0;
    bits |= g.rightShoulder.pressed ? SHELL_PAD_SHOULDER_R : 0;
    return bits;
}

/* --- the window ---------------------------------------------------------------------------- */

@interface ShellView : NSView
@property(strong) CALayer *picture;
@property(strong) NSCursor *blank;
@property NSSize source; /* the frame's size in pixels */
@end

@implementation ShellView

- (instancetype)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    self.wantsLayer = YES;
    self.layer.backgroundColor = NSColor.blackColor.CGColor;
    self.picture = [CALayer layer];
    self.picture.contentsGravity = kCAGravityResize;
    self.picture.actions =
        @{@"contents" : [NSNull null], @"bounds" : [NSNull null], @"position" : [NSNull null]};
    [self.layer addSublayer:self.picture];
    self.source = NSMakeSize(options.width, options.height);
    NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(1, 1)];
    self.blank = [[NSCursor alloc] initWithImage:image hotSpot:NSZeroPoint];
    [self addTrackingArea:[[NSTrackingArea alloc]
                              initWithRect:NSZeroRect
                                   options:NSTrackingMouseMoved | NSTrackingActiveInKeyWindow |
                                           NSTrackingInVisibleRect | NSTrackingCursorUpdate
                                     owner:self
                                  userInfo:nil]];
    return self;
}

- (BOOL)isFlipped
{
    return YES;
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (double)aspect
{
    return options.aspect > 0 ? options.aspect : self.source.width / self.source.height;
}

/* The picture's place in the view: as large as fits, at its shape, centred. */
- (NSRect)pictureRect
{
    const NSRect b = self.bounds;
    const double aspect = [self aspect];
    double w = b.size.width, h = w / aspect;
    if (h > b.size.height)
    {
        h = b.size.height;
        w = h * aspect;
    }
    return NSMakeRect(round((b.size.width - w) / 2), round((b.size.height - h) / 2), round(w),
                      round(h));
}

- (void)layout
{
    [super layout];
    const NSRect r = [self pictureRect];
    self.picture.frame = r;
    /* Sharp pixels from twice the size up, smooth below (a small window). */
    const double scale = self.window.backingScaleFactor;
    const double sx = r.size.width * scale / self.source.width;
    const double sy = r.size.height * scale / self.source.height;
    self.picture.magnificationFilter = sx >= 2 && sy >= 2 ? kCAFilterNearest : kCAFilterLinear;
    [self.window invalidateCursorRectsForView:self];
}

- (void)resetCursorRects
{
    if (options.hide_cursor)
    {
        [self addCursorRect:[self pictureRect] cursor:self.blank];
    }
}

- (void)cursorUpdate:(NSEvent *)event
{
    const NSPoint p = [self convertPoint:event.locationInWindow fromView:nil];
    if (options.hide_cursor && NSPointInRect(p, [self pictureRect]))
    {
        [self.blank set];
    }
    else
    {
        [NSCursor.arrowCursor set];
    }
}

- (void)keyDown:(NSEvent *)event
{
    if (event.modifierFlags & NSEventModifierFlagCommand)
    {
        [super keyDown:event];
        return;
    }
    key(event.keyCode, 1, event.isARepeat);
}

- (void)keyUp:(NSEvent *)event
{
    key(event.keyCode, 0, 0);
}

- (void)flagsChanged:(NSEvent *)event
{
    const unsigned code = event.keyCode;
    if (code == 0x39) /* Caps Lock: one press for each change */
    {
        key(code, 1, 0);
        key(code, 0, 0);
        return;
    }
    for (unsigned k = 0; k < sizeof modifiers / sizeof modifiers[0]; ++k)
    {
        if (modifiers[k].key == code)
        {
            key(code, (event.modifierFlags & modifiers[k].mask) != 0, 0);
        }
    }
}

- (void)mouseDown:(NSEvent *)event
{
    button(0, 1);
}

- (void)mouseUp:(NSEvent *)event
{
    button(0, 0);
}

- (void)rightMouseDown:(NSEvent *)event
{
    button(1, 1);
}

- (void)rightMouseUp:(NSEvent *)event
{
    button(1, 0);
}

- (void)otherMouseDown:(NSEvent *)event
{
    button(2, 1);
}

- (void)otherMouseUp:(NSEvent *)event
{
    button(2, 0);
}

/* Once a refresh: the driver's picture, the newest frame, the pointer and the pads. */
- (void)refresh
{
    if (refresh_hook)
    {
        refresh_hook();
    }
    CGImageRef image = NULL;
    pthread_mutex_lock(&frame_lock);
    if (frame_new)
    {
        frame_new = 0;
        const size_t bytes = (size_t)frame_width * frame_height * 4u;
        CFDataRef data = CFDataCreate(NULL, (const UInt8 *)frame_pixels, (CFIndex)bytes);
        CGDataProviderRef provider = CGDataProviderCreateWithCFData(data);
        CGColorSpaceRef space = CGColorSpaceCreateWithName(kCGColorSpaceSRGB);
        image = CGImageCreate(frame_width, frame_height, 8, 32, frame_width * 4u, space,
                              kCGBitmapByteOrder32Little | kCGImageAlphaNoneSkipFirst, provider,
                              NULL, false, kCGRenderingIntentDefault);
        CGColorSpaceRelease(space);
        CGDataProviderRelease(provider);
        CFRelease(data);
    }
    pthread_mutex_unlock(&frame_lock);
    if (image)
    {
        const NSSize size = NSMakeSize(CGImageGetWidth(image), CGImageGetHeight(image));
        if (!NSEqualSizes(size, self.source))
        {
            self.source = size;
            if (options.aspect <= 0)
            {
                self.window.contentAspectRatio = size;
            }
            self.needsLayout = YES;
        }
        self.picture.contents = (__bridge id)image;
        CGImageRelease(image);
    }

    const NSRect r = [self pictureRect];
    const NSPoint p = [self convertPoint:self.window.mouseLocationOutsideOfEventStream
                                fromView:nil];
    const double x = (p.x - r.origin.x) * self.source.width / r.size.width;
    const double y = (p.y - r.origin.y) * self.source.height / r.size.height;
    pointer_x = x < 0 ? 0 : x >= self.source.width ? (int)self.source.width - 1 : (int)x;
    pointer_y = y < 0 ? 0 : y >= self.source.height ? (int)self.source.height - 1 : (int)y;
    pointer_inside = NSPointInRect(p, self.bounds);

    NSArray<GCController *> *controllers = GCController.controllers;
    for (unsigned i = 0; i < 2; ++i)
    {
        pads[i] = i < controllers.count && NSApp.isActive ? read_pad(controllers[i]) : 0;
    }
}

@end

@interface ShellDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@property(strong) NSWindow *window;
@property(strong) ShellView *view;
@end

@implementation ShellDelegate

- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender
{
    /* The game leaves through its own exit, which ends the app; a second Quit after a few
     * seconds ends it at once. */
    if (quit_asked && shell_microseconds() - quit_time > 3000000u)
    {
        return NSTerminateNow;
    }
    ask_quit();
    return NSTerminateCancel;
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    ask_quit();
    return NO;
}

- (void)windowDidResignKey:(NSNotification *)notification
{
    release_all();
}

- (void)tick:(NSTimer *)timer
{
    [self.view refresh];
}

- (void)setScale:(NSMenuItem *)item
{
    if (self.window.styleMask & NSWindowStyleMaskFullScreen)
    {
        return;
    }
    const double aspect = [self.view aspect];
    const double h = options.height * (double)item.tag;
    NSRect frame = [self.window frameRectForContentRect:NSMakeRect(0, 0, round(h * aspect), h)];
    frame.origin = self.window.frame.origin;
    frame.origin.y += self.window.frame.size.height - frame.size.height;
    [self.window setFrame:frame display:YES animate:YES];
}

- (void)showFolder:(id)sender
{
    [NSWorkspace.sharedWorkspace openURL:[NSURL fileURLWithPath:@(folder)]];
}

@end

static ShellDelegate *delegate;

static NSMenuItem *item(NSString *title, SEL action, NSString *key)
{
    return [[NSMenuItem alloc] initWithTitle:title action:action keyEquivalent:key];
}

static void build_menus(NSString *title)
{
    NSMenu *bar = [[NSMenu alloc] init];
    NSMenu *app = [[NSMenu alloc] initWithTitle:title];
    [app addItem:item([@"About " stringByAppendingString:title],
                      @selector(orderFrontStandardAboutPanel:), @"")];
    [app addItem:NSMenuItem.separatorItem];
    [app addItem:item([@"Hide " stringByAppendingString:title], @selector(hide:), @"h")];
    NSMenuItem *others = item(@"Hide Others", @selector(hideOtherApplications:), @"h");
    others.keyEquivalentModifierMask = NSEventModifierFlagCommand | NSEventModifierFlagOption;
    [app addItem:others];
    [app addItem:item(@"Show All", @selector(unhideAllApplications:), @"")];
    [app addItem:NSMenuItem.separatorItem];
    [app addItem:item([@"Quit " stringByAppendingString:title], @selector(terminate:), @"q")];

    NSMenu *file = [[NSMenu alloc] initWithTitle:@"File"];
    NSMenuItem *show = item(@"Show Game Folder", @selector(showFolder:), @"");
    show.target = delegate;
    [file addItem:show];
    [file addItem:item(@"Close", @selector(performClose:), @"w")];

    NSMenu *view = [[NSMenu alloc] initWithTitle:@"View"];
    for (int scale = 1; scale <= 3; ++scale)
    {
        NSString *names[] = {@"", @"Actual Size", @"Double Size", @"Triple Size"};
        NSMenuItem *size =
            item(names[scale], @selector(setScale:), [NSString stringWithFormat:@"%d", scale]);
        size.tag = scale;
        size.target = delegate;
        [view addItem:size];
    }
    [view addItem:NSMenuItem.separatorItem];
    NSMenuItem *full = item(@"Enter Full Screen", @selector(toggleFullScreen:), @"f");
    full.keyEquivalentModifierMask = NSEventModifierFlagCommand | NSEventModifierFlagControl;
    [view addItem:full];

    NSMenu *window = [[NSMenu alloc] initWithTitle:@"Window"];
    [window addItem:item(@"Minimize", @selector(performMiniaturize:), @"m")];
    [window addItem:item(@"Zoom", @selector(performZoom:), @"")];

    for (NSMenu *menu in @[ app, file, view, window ])
    {
        NSMenuItem *top = [[NSMenuItem alloc] init];
        top.submenu = menu;
        [bar addItem:top];
    }
    NSApp.mainMenu = bar;
    NSApp.windowsMenu = window;
}

static void open_window(NSString *title)
{
    /* The largest whole multiple of the picture that fits the screen. */
    const NSRect screen = NSScreen.mainScreen.visibleFrame;
    const double aspect =
        options.aspect > 0 ? options.aspect : (double)options.width / options.height;
    int scale = 1;
    while (options.height * (scale + 1) * aspect < screen.size.width * 0.9 &&
           options.height * (scale + 1) < screen.size.height * 0.9)
    {
        ++scale;
    }
    const NSRect content =
        NSMakeRect(0, 0, round(options.height * scale * aspect), options.height * scale);
    NSWindow *window = [[NSWindow alloc]
        initWithContentRect:content
                  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                            NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
                    backing:NSBackingStoreBuffered
                      defer:NO];
    window.title = title;
    window.delegate = delegate;
    window.contentAspectRatio = content.size;
    window.contentMinSize = NSMakeSize(round(240 * aspect), 240);
    window.collectionBehavior = NSWindowCollectionBehaviorFullScreenPrimary;
    window.backgroundColor = NSColor.blackColor;
    window.acceptsMouseMovedEvents = YES;
    window.releasedWhenClosed = NO;
    delegate.view = [[ShellView alloc] initWithFrame:content];
    window.contentView = delegate.view;
    [window makeFirstResponder:delegate.view];
    [window center];
    window.frameAutosaveName = @"Game"; /* the size and place of the last run, when saved */
    delegate.window = window;
    [window makeKeyAndOrderFront:nil];
    NSTimer *timer = [NSTimer timerWithTimeInterval:1.0 / 60.0
                                             target:delegate
                                           selector:@selector(tick:)
                                           userInfo:nil
                                            repeats:YES];
    timer.tolerance = 0.002;
    [NSRunLoop.mainRunLoop addTimer:timer forMode:NSRunLoopCommonModes];
}

const char *shell_start(int argc, char **argv, const ShellOptions *start)
{
    options = *start;
    [NSApplication sharedApplication];
    NSApp.activationPolicy = NSApplicationActivationPolicyRegular;
    delegate = [[ShellDelegate alloc] init];
    NSApp.delegate = delegate;
    NSString *title = @(options.game->title);
    build_menus(title);
    [NSApp finishLaunching];

    folder[0] = 0;
    for (int i = 1; i + 1 < argc; ++i)
    {
        if (strcmp(argv[i], "--data") == 0)
        {
            snprintf(folder, sizeof folder, "%s", argv[i + 1]);
        }
    }
    if (!folder[0])
    {
        snprintf(folder, sizeof folder, "%s", vertrix_game_folder(options.game));
    }
    [NSFileManager.defaultManager createDirectoryAtPath:@(folder)
                            withIntermediateDirectories:YES
                                             attributes:nil
                                                  error:nil];
    if (!vertrix_game_ready(options.game, folder) && !vertrix_import_bundled(options.game, folder))
    {
        [NSApp activateIgnoringOtherApps:YES];
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText =
            [NSString stringWithFormat:@"%s needs the original game's files.", options.game->title];
        alert.informativeText = [NSString
            stringWithFormat:@"Choose %s from your own copy of the game. It is copied into %s.",
                             options.game->needs_text, folder];
        [alert addButtonWithTitle:@"Choose…"];
        [alert addButtonWithTitle:@"Quit"];
        if ([alert runModal] != NSAlertFirstButtonReturn ||
            !vertrix_import_ask(options.game, folder))
        {
            exit(0);
        }
    }
    open_window(title);
    [NSApp activateIgnoringOtherApps:YES];
    return folder;
}

uint8_t *shell_resource(const char *name, size_t *size)
{
    NSString *path = [NSBundle.mainBundle pathForResource:@(name) ofType:nil];
    if (!path)
    {
        /* Run from the build folder, not a bundle: next to the executable. */
        path = [NSBundle.mainBundle.executablePath.stringByDeletingLastPathComponent
            stringByAppendingPathComponent:@(name)];
    }
    NSData *data = [NSData dataWithContentsOfFile:path];
    if (!data)
    {
        return NULL;
    }
    uint8_t *bytes = malloc(data.length);
    memcpy(bytes, data.bytes, data.length);
    *size = data.length;
    return bytes;
}

static void (*game_main)(void);

static void *game_thread(void *unused)
{
    (void)unused;
    game_main();
    exit(0);
}

_Noreturn void shell_run(void (*game)(void))
{
    game_main = game;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 256u << 20);
    pthread_t thread;
    pthread_create(&thread, &attr, game_thread, NULL);
    [NSApp run];
    exit(0);
}

/* --- sound --------------------------------------------------------------------------------- */

/* A ring of 16-bit samples the output unit pulls from; 8-bit samples are widened on the way in,
 * and the counts the driver sees are in its own bytes. */
enum
{
    RING = 1u << 21
};
static int16_t *ring;
static _Atomic uint64_t ring_written, ring_read; /* in samples */
static AudioComponentInstance unit;
static uint32_t audio_rate, audio_channels, audio_bits;

static OSStatus render(void *context, AudioUnitRenderActionFlags *flags,
                       const AudioTimeStamp *stamp, UInt32 bus, UInt32 frames,
                       AudioBufferList *buffers)
{
    (void)context;
    (void)flags;
    (void)stamp;
    (void)bus;
    int16_t *out = buffers->mBuffers[0].mData;
    const uint64_t want = buffers->mBuffers[0].mDataByteSize / 2u;
    const uint64_t read = ring_read, written = ring_written;
    uint64_t have = written - read < want ? written - read : want;
    have -= have % audio_channels;
    for (uint64_t i = 0; i < have; ++i)
    {
        out[i] = ring[(read + i) % RING];
    }
    memset(out + have, 0, (size_t)(want - have) * 2u);
    ring_read = read + have;
    return noErr;
}

void shell_audio_open(uint32_t rate, uint32_t channels, uint32_t bits)
{
    if (!ring)
    {
        ring = calloc(RING, sizeof *ring);
        AudioComponentDescription d = {kAudioUnitType_Output, kAudioUnitSubType_DefaultOutput,
                                       kAudioUnitManufacturer_Apple, 0, 0};
        AudioComponent component = AudioComponentFindNext(NULL, &d);
        if (!component || AudioComponentInstanceNew(component, &unit) != noErr)
        {
            shell_log("sound: no output device");
            unit = NULL;
            return;
        }
        AURenderCallbackStruct callback = {render, NULL};
        AudioUnitSetProperty(unit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0,
                             &callback, sizeof callback);
    }
    if (!unit)
    {
        return;
    }
    AudioOutputUnitStop(unit);
    AudioUnitUninitialize(unit);
    ring_read = 0;
    ring_written = 0;
    audio_rate = rate;
    audio_channels = channels ? channels : 1;
    audio_bits = bits;
    AudioStreamBasicDescription f = {0};
    f.mSampleRate = rate;
    f.mFormatID = kAudioFormatLinearPCM;
    f.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    f.mChannelsPerFrame = audio_channels;
    f.mBitsPerChannel = 16;
    f.mBytesPerFrame = 2u * audio_channels;
    f.mFramesPerPacket = 1;
    f.mBytesPerPacket = f.mBytesPerFrame;
    AudioUnitSetProperty(unit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &f,
                         sizeof f);
    if (AudioUnitInitialize(unit) != noErr || AudioOutputUnitStart(unit) != noErr)
    {
        shell_log("sound: the output device refused the format");
        return;
    }
    char line[96];
    snprintf(line, sizeof line, "sound: %u Hz, %u channels, %u bits", rate, channels, bits);
    shell_log(line);
}

void shell_audio_write(const uint8_t *samples, uint32_t bytes)
{
    if (!unit || !audio_bits)
    {
        return;
    }
    const uint32_t size = audio_bits == 8 ? 1u : 2u;
    uint32_t count = bytes / size;
    /* Wait for room (the game queues only a few buffers ahead); after a second, drop. */
    for (int tries = 0; RING - (ring_written - ring_read) < count && tries < 500; ++tries)
    {
        usleep(2000);
    }
    const uint64_t room = RING - (ring_written - ring_read);
    if (count > room)
    {
        count = (uint32_t)room;
    }
    const uint64_t at = ring_written;
    for (uint32_t i = 0; i < count; ++i)
    {
        ring[(at + i) % RING] = size == 1 ? (int16_t)((samples[i] - 128) << 8)
                                          : (int16_t)(samples[2 * i] | samples[2 * i + 1] << 8);
    }
    ring_written = at + count;
}

uint64_t shell_audio_played(void)
{
    return ring_read * (audio_bits == 8 ? 1u : 2u);
}

uint32_t shell_audio_queued(void)
{
    return (uint32_t)(ring_written - ring_read) * (audio_bits == 8 ? 1u : 2u);
}
