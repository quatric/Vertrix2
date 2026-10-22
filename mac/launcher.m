/* Vertrix.app: the Mac's counterpart of the Wii launcher (launcher/main.c). One window lists the
 * four games and plays the soundtrack (mac/README.md):
 *
 *   Vertrix.app/Contents/MacOS/Vertrix            this launcher
 *   Vertrix.app/Contents/Helpers/<folder>.app      the games (vertrix_games.h)
 *   Vertrix.app/Contents/Resources/Music/<album>/  albums a build carries (MAC_MUSIC=)
 *   <Vertrix folder>/music/<album>/                the player's own albums
 *
 * A game runs as its own app with its own window and menus; this window hides while it runs and
 * comes back when it ends, as the Wii's menu does. Each game asks for its files itself the first
 * time (mac/data.h). Albums are folders of MP3, M4A or WAV files; an optional album.txt names
 * one (its first line), as on the Wii. */
#import <AVFoundation/AVFoundation.h>
#import <Cocoa/Cocoa.h>

#include "data.h"

/* --- music --------------------------------------------------------------------------------- */

@interface Album : NSObject
@property(copy) NSString *name;
@property(copy) NSArray<NSURL *> *tracks;
@property(copy) NSArray<NSString *> *titles;
@end

@implementation Album
@end

static NSArray<NSString *> *music_folders(void)
{
    return @[
        [NSBundle.mainBundle.resourcePath stringByAppendingPathComponent:@"Music"],
        [@(vertrix_home()) stringByAppendingPathComponent:@"music"]
    ];
}

/* The tracks' names without what all of them start with up to a " - " (the artist and album of
 * "The Clusters - Vertrix 2 - 01 - Introduction.mp3"). */
static NSArray<NSString *> *track_titles(NSArray<NSURL *> *tracks)
{
    NSMutableArray<NSString *> *names = [NSMutableArray array];
    for (NSURL *track in tracks)
    {
        [names addObject:track.lastPathComponent.stringByDeletingPathExtension];
    }
    NSString *common = names.firstObject;
    for (NSString *name in names)
    {
        common = [common commonPrefixWithString:name options:0];
    }
    const NSRange cut = [common rangeOfString:@" - " options:NSBackwardsSearch];
    if (names.count < 2 || cut.location == NSNotFound)
    {
        return names;
    }
    NSMutableArray<NSString *> *titles = [NSMutableArray array];
    for (NSString *name in names)
    {
        [titles addObject:[name substringFromIndex:NSMaxRange(cut)]];
    }
    return titles;
}

static NSArray<Album *> *find_albums(void)
{
    NSFileManager *files = NSFileManager.defaultManager;
    NSSet *kinds = [NSSet setWithArray:@[ @"mp3", @"m4a", @"aac", @"wav", @"aif", @"aiff" ]];
    NSMutableArray<Album *> *albums = [NSMutableArray array];
    for (NSString *root in music_folders())
    {
        NSArray *names = [[files contentsOfDirectoryAtPath:root error:nil]
            sortedArrayUsingSelector:@selector(localizedStandardCompare:)];
        for (NSString *name in names)
        {
            NSString *folder = [root stringByAppendingPathComponent:name];
            NSMutableArray<NSURL *> *tracks = [NSMutableArray array];
            NSArray *entries = [[files contentsOfDirectoryAtPath:folder error:nil]
                sortedArrayUsingSelector:@selector(localizedStandardCompare:)];
            for (NSString *entry in entries)
            {
                if ([kinds containsObject:entry.pathExtension.lowercaseString])
                {
                    [tracks
                        addObject:[NSURL
                                      fileURLWithPath:[folder
                                                          stringByAppendingPathComponent:entry]]];
                }
            }
            if (tracks.count == 0)
            {
                continue;
            }
            Album *album = [[Album alloc] init];
            album.name = name;
            NSString *text = [NSString
                stringWithContentsOfFile:[folder stringByAppendingPathComponent:@"album.txt"]
                                encoding:NSUTF8StringEncoding
                                   error:nil];
            NSString *first =
                [text componentsSeparatedByCharactersInSet:NSCharacterSet.newlineCharacterSet]
                    .firstObject;
            first = [first stringByTrimmingCharactersInSet:NSCharacterSet.whitespaceCharacterSet];
            if (first.length)
            {
                album.name = first;
            }
            album.tracks = tracks;
            album.titles = track_titles(tracks);
            [albums addObject:album];
        }
    }
    return albums;
}

/* --- the window ---------------------------------------------------------------------------- */

@interface Launcher : NSObject <NSApplicationDelegate, NSTableViewDataSource, NSTableViewDelegate,
                                AVAudioPlayerDelegate>
@property(strong) NSWindow *window;
@property(strong) NSTableView *games, *tracks;
@property(strong) NSPopUpButton *albumMenu;
@property(strong) NSButton *playButton, *pauseButton, *shuffle;
@property(strong) NSTextField *nowPlaying;
@property(strong) NSArray<Album *> *albums;
@property(strong) AVAudioPlayer *player;
@property NSInteger album, track;
@property(strong) NSRunningApplication *running;
@property(strong) dispatch_source_t exitWatch;
@end

static NSTextField *label(NSString *text, CGFloat size, BOOL bold)
{
    NSTextField *field = [NSTextField labelWithString:text];
    field.font = bold ? [NSFont boldSystemFontOfSize:size] : [NSFont systemFontOfSize:size];
    field.translatesAutoresizingMaskIntoConstraints = NO;
    return field;
}

static NSButton *button(NSString *title, id target, SEL action)
{
    NSButton *b = [NSButton buttonWithTitle:title target:target action:action];
    b.translatesAutoresizingMaskIntoConstraints = NO;
    return b;
}

static NSScrollView *scrolled(NSTableView *table)
{
    NSScrollView *scroll = [[NSScrollView alloc] init];
    scroll.documentView = table;
    scroll.hasVerticalScroller = YES;
    scroll.borderType = NSBezelBorder;
    scroll.translatesAutoresizingMaskIntoConstraints = NO;
    return scroll;
}

@implementation Launcher

- (NSURL *)helperFor:(const VertrixGame *)game
{
    NSString *path =
        [[NSBundle.mainBundle.bundlePath stringByAppendingPathComponent:@"Contents/Helpers"]
            stringByAppendingPathComponent:[@(game->folder) stringByAppendingPathExtension:@"app"]];
    return [NSFileManager.defaultManager fileExistsAtPath:path] ? [NSURL fileURLWithPath:path]
                                                                : nil;
}

- (NSString *)statusOf:(const VertrixGame *)game
{
    if (![self helperFor:game])
    {
        return @"Not in this build";
    }
    NSString *folder = [@(vertrix_home()) stringByAppendingPathComponent:@(game->folder)];
    if ([NSFileManager.defaultManager fileExistsAtPath:folder] &&
        vertrix_game_ready(game, folder.fileSystemRepresentation))
    {
        return @"Ready";
    }
    return [NSString stringWithFormat:@"Needs %s", game->needs];
}

- (NSTableView *)tableWith:(NSArray<NSString *> *)columns widths:(NSArray<NSNumber *> *)widths
{
    NSTableView *table = [[NSTableView alloc] init];
    for (NSUInteger i = 0; i < columns.count; ++i)
    {
        NSTableColumn *column = [[NSTableColumn alloc] initWithIdentifier:columns[i]];
        column.title = columns[i];
        column.width = widths[i].doubleValue;
        [table addTableColumn:column];
    }
    table.dataSource = self;
    table.delegate = self;
    table.usesAlternatingRowBackgroundColors = YES;
    table.columnAutoresizingStyle = NSTableViewLastColumnOnlyAutoresizingStyle;
    table.target = self;
    return table;
}

- (void)build
{
    self.window = [[NSWindow alloc]
        initWithContentRect:NSMakeRect(0, 0, 640, 600)
                  styleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                            NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable
                    backing:NSBackingStoreBuffered
                      defer:NO];
    self.window.title = @"Vertrix";
    self.window.contentMinSize = NSMakeSize(520, 480);
    self.window.releasedWhenClosed = NO;
    NSView *view = self.window.contentView;

    NSImageView *logo = [[NSImageView alloc] init];
    logo.image = [NSImage imageNamed:@"Logo"];
    logo.imageScaling = NSImageScaleProportionallyUpOrDown;
    logo.translatesAutoresizingMaskIntoConstraints = NO;

    self.games = [self tableWith:@[ @"Game", @"Year", @"", @"Files" ]
                          widths:@[ @130, @44, @170, @220 ]];
    self.games.rowHeight = 22;
    self.games.doubleAction = @selector(play:);
    NSButton *play = button(@"Play", self, @selector(play:));
    play.keyEquivalent = @"\r";
    NSButton *folder = button(@"Show Files", self, @selector(showGameFolder:));

    self.albumMenu = [[NSPopUpButton alloc] init];
    self.albumMenu.translatesAutoresizingMaskIntoConstraints = NO;
    self.albumMenu.target = self;
    self.albumMenu.action = @selector(chooseAlbum:);
    self.tracks = [self tableWith:@[ @"Track" ] widths:@[ @560 ]];
    self.tracks.doubleAction = @selector(playTrack:);
    self.playButton = button(@"Play", self, @selector(playTrack:));
    self.pauseButton = button(@"Pause", self, @selector(pause:));
    NSButton *next = button(@"Next", self, @selector(next:));
    /* Shuffle is on until the player turns it off (remembered). */
    [NSUserDefaults.standardUserDefaults registerDefaults:@{@"Shuffle" : @YES}];
    self.shuffle = [NSButton checkboxWithTitle:@"Shuffle"
                                        target:self
                                        action:@selector(shuffleChanged:)];
    self.shuffle.state = [NSUserDefaults.standardUserDefaults boolForKey:@"Shuffle"]
                             ? NSControlStateValueOn
                             : NSControlStateValueOff;
    self.shuffle.translatesAutoresizingMaskIntoConstraints = NO;
    NSButton *music = button(@"Show Music Folder", self, @selector(showMusicFolder:));
    self.nowPlaying = label(@"", 12, NO);
    self.nowPlaying.textColor = NSColor.secondaryLabelColor;
    self.nowPlaying.lineBreakMode = NSLineBreakByTruncatingTail;

    NSTextField *gamesTitle = label(@"Games", 15, YES);
    NSTextField *musicTitle = label(@"Soundtrack", 15, YES);
    NSScrollView *gamesScroll = scrolled(self.games);
    NSScrollView *tracksScroll = scrolled(self.tracks);
    for (NSView *v in @[
             logo, gamesTitle, gamesScroll, play, folder, musicTitle, self.albumMenu, tracksScroll,
             self.playButton, self.pauseButton, next, self.shuffle, music, self.nowPlaying
         ])
    {
        [view addSubview:v];
    }
    NSDictionary *v = NSDictionaryOfVariableBindings(logo, gamesTitle, gamesScroll, play, folder,
                                                     musicTitle, tracksScroll, next, music);
    NSDictionary *more = @{
        @"albums" : self.albumMenu,
        @"playTrack" : self.playButton,
        @"pause" : self.pauseButton,
        @"shuffle" : self.shuffle,
        @"now" : self.nowPlaying
    };
    NSMutableDictionary *all = [v mutableCopy];
    [all addEntriesFromDictionary:more];
    NSString *vertical = @"V:|-12-[logo(72)]-10-[gamesTitle]-6-[gamesScroll(118)]-8-[play]-14-"
                         @"[musicTitle]-6-[tracksScroll(>=100)]-8-[playTrack]-6-[now]-12-|";
    NSArray *rules = @[
        @"H:|-16-[logo]-16-|", @"H:|-16-[gamesTitle]", @"H:|-16-[gamesScroll]-16-|",
        @"H:[folder]-8-[play(>=80)]-16-|", @"H:|-16-[musicTitle]-12-[albums(>=200)]",
        @"H:|-16-[tracksScroll]-16-|",
        @"H:|-16-[playTrack(>=70)]-8-[pause]-8-[next]-12-[shuffle]-(>=12)-[music]-16-|",
        @"H:|-16-[now]-16-|", vertical
    ];
    for (NSString *rule in rules)
    {
        [view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:rule
                                                                     options:0
                                                                     metrics:nil
                                                                       views:all]];
    }
    for (NSView *row in @[ folder ])
    {
        [row.centerYAnchor constraintEqualToAnchor:play.centerYAnchor].active = YES;
    }
    [self.albumMenu.centerYAnchor constraintEqualToAnchor:musicTitle.centerYAnchor].active = YES;
    for (NSView *row in @[ self.pauseButton, next, self.shuffle, music ])
    {
        [row.centerYAnchor constraintEqualToAnchor:self.playButton.centerYAnchor].active = YES;
    }
    [self.window center];
    self.window.frameAutosaveName = @"Launcher";
}

- (void)loadAlbums
{
    self.albums = find_albums();
    [self.albumMenu removeAllItems];
    for (Album *album in self.albums)
    {
        [self.albumMenu addItemWithTitle:album.name];
    }
    if (self.albums.count == 0)
    {
        [self.albumMenu addItemWithTitle:@"No albums"];
        self.albumMenu.enabled = NO;
        self.nowPlaying.stringValue = [NSString
            stringWithFormat:@"Put albums (folders of MP3 files) in %@.", music_folders()[1]];
    }
    self.album = 0;
    [self.tracks reloadData];
}

- (void)applicationDidFinishLaunching:(NSNotification *)notification
{
    [self build];
    [self loadAlbums];
    [self updateButtons];
    [self.games reloadData];
    [self.games selectRowIndexes:[NSIndexSet indexSetWithIndex:0] byExtendingSelection:NO];
    self.games.allowsEmptySelection = NO;
    [self.window makeKeyAndOrderFront:nil];
    [self.window makeFirstResponder:self.games];
    [NSApp activateIgnoringOtherApps:YES];
    /* The soundtrack starts with the launcher on a random track. */
    [self playRandom];
}

- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)visible
{
    if (!visible && !self.running)
    {
        [self.window makeKeyAndOrderFront:nil];
    }
    else if (self.running)
    {
        [self.running activateWithOptions:0];
    }
    return NO;
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return self.running == nil;
}

- (void)applicationDidBecomeActive:(NSNotification *)notification
{
    [self.games reloadData];
}

/* --- games --- */

- (void)play:(id)sender
{
    const NSInteger row = self.games.selectedRow;
    if (row < 0 || self.running)
    {
        return;
    }
    const VertrixGame *game = &vertrix_games[row];
    NSURL *helper = [self helperFor:game];
    if (!helper)
    {
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = [NSString stringWithFormat:@"%s is not in this build.", game->title];
        [alert runModal];
        return;
    }
    [self.player pause];
    [self updateButtons];
    NSWorkspaceOpenConfiguration *configuration = [NSWorkspaceOpenConfiguration configuration];
    configuration.activates = YES;
    configuration.addsToRecentItems = NO;
    /* An app started this way does not inherit this one's environment: pass the folder on. */
    configuration.environment = @{@"VERTRIX_HOME" : @(vertrix_home())};
    [NSWorkspace.sharedWorkspace openApplicationAtURL:helper
                                        configuration:configuration
                                    completionHandler:^(NSRunningApplication *app, NSError *error) {
                                      dispatch_async(dispatch_get_main_queue(), ^{
                                        if (error)
                                        {
                                            [[NSAlert alertWithError:error] runModal];
                                            return;
                                        }
                                        self.running = app;
                                        [self.window orderOut:nil];
                                        [self watch:app];
                                      });
                                    }];
}

/* Brings the window back when the game's process ends, however it ends. */
- (void)watch:(NSRunningApplication *)app
{
    self.exitWatch =
        dispatch_source_create(DISPATCH_SOURCE_TYPE_PROC, (uintptr_t)app.processIdentifier,
                               DISPATCH_PROC_EXIT, dispatch_get_main_queue());
    dispatch_source_set_event_handler(self.exitWatch, ^{
      [self ended];
    });
    dispatch_resume(self.exitWatch);
    if (app.terminated)
    {
        [self ended];
    }
}

- (void)ended
{
    if (!self.running)
    {
        return;
    }
    dispatch_source_cancel(self.exitWatch);
    self.exitWatch = nil;
    self.running = nil;
    [self.games reloadData];
    [self.window makeKeyAndOrderFront:nil];
    [NSApp activateIgnoringOtherApps:YES];
}

- (void)showGameFolder:(id)sender
{
    const NSInteger row = MAX(self.games.selectedRow, 0);
    NSString *folder = @(vertrix_game_folder(&vertrix_games[row]));
    [NSWorkspace.sharedWorkspace openURL:[NSURL fileURLWithPath:folder]];
}

- (void)showFolder:(id)sender
{
    [NSWorkspace.sharedWorkspace openURL:[NSURL fileURLWithPath:@(vertrix_home())]];
}

/* --- music --- */

/* The album the list shows (the one playing is self.album). */
- (Album *)currentAlbum
{
    const NSInteger shown = self.albumMenu.indexOfSelectedItem;
    return shown >= 0 && shown < (NSInteger)self.albums.count ? self.albums[shown] : nil;
}

- (void)chooseAlbum:(id)sender
{
    [self.tracks reloadData];
}

- (void)updateButtons
{
    self.pauseButton.title = self.player && !self.player.playing ? @"Resume" : @"Pause";
    self.pauseButton.enabled = self.player != nil;
}

- (void)start:(NSInteger)track ofAlbum:(NSInteger)album
{
    Album *a = self.albums[album];
    NSError *error = nil;
    self.player = [[AVAudioPlayer alloc] initWithContentsOfURL:a.tracks[track] error:&error];
    if (!self.player)
    {
        self.nowPlaying.stringValue = error.localizedDescription ?: @"That track cannot be played.";
        return;
    }
    self.player.delegate = self;
    [self.player play];
    self.album = album;
    self.track = track;
    [self.albumMenu selectItemAtIndex:album];
    [self.tracks reloadData];
    [self.tracks selectRowIndexes:[NSIndexSet indexSetWithIndex:track] byExtendingSelection:NO];
    [self.tracks scrollRowToVisible:track];
    self.nowPlaying.stringValue =
        [NSString stringWithFormat:@"Playing %@ (%@)", a.titles[track], a.name];
    [self updateButtons];
}

- (void)playTrack:(id)sender
{
    Album *album = [self currentAlbum];
    if (!album)
    {
        return;
    }
    [self start:MAX(self.tracks.selectedRow, 0) ofAlbum:self.albumMenu.indexOfSelectedItem];
}

- (void)pause:(id)sender
{
    if (self.player.playing)
    {
        [self.player pause];
    }
    else
    {
        [self.player play];
    }
    [self updateButtons];
}

- (void)shuffleChanged:(id)sender
{
    [NSUserDefaults.standardUserDefaults setBool:self.shuffle.state == NSControlStateValueOn
                                          forKey:@"Shuffle"];
}

/* Any track of any album but the one playing. */
- (void)playRandom
{
    NSUInteger total = 0;
    for (Album *a in self.albums)
    {
        total += a.tracks.count;
    }
    if (total == 0)
    {
        return;
    }
    for (int tries = 0;; ++tries)
    {
        NSUInteger pick = arc4random_uniform((uint32_t)total);
        NSInteger album = 0;
        while (pick >= self.albums[album].tracks.count)
        {
            pick -= self.albums[album].tracks.count;
            ++album;
        }
        if (tries == 8 || total < 2 || !self.player || album != self.album ||
            (NSInteger)pick != self.track)
        {
            [self start:(NSInteger)pick ofAlbum:album];
            return;
        }
    }
}

/* The next track: a random one in shuffle, otherwise the next of the album. */
- (void)next:(id)sender
{
    if (self.albums.count == 0)
    {
        return;
    }
    if (self.shuffle.state == NSControlStateValueOn)
    {
        [self playRandom];
        return;
    }
    const NSInteger album = self.player ? self.album : self.albumMenu.indexOfSelectedItem;
    const NSInteger count = (NSInteger)self.albums[album].tracks.count;
    [self start:(self.player ? self.track + 1 : 0) % count ofAlbum:album];
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag
{
    [self next:nil];
}

- (void)showMusicFolder:(id)sender
{
    NSString *folder = music_folders()[1];
    [NSFileManager.defaultManager createDirectoryAtPath:folder
                            withIntermediateDirectories:YES
                                             attributes:nil
                                                  error:nil];
    [NSWorkspace.sharedWorkspace openURL:[NSURL fileURLWithPath:folder]];
    [self loadAlbums];
}

/* --- tables --- */

- (NSInteger)numberOfRowsInTableView:(NSTableView *)table
{
    return table == self.games ? VERTRIX_GAMES : (NSInteger)[self currentAlbum].tracks.count;
}

- (NSView *)tableView:(NSTableView *)table
    viewForTableColumn:(NSTableColumn *)column
                   row:(NSInteger)row
{
    NSTableCellView *cell = [table makeViewWithIdentifier:column.identifier owner:self];
    if (!cell)
    {
        cell = [[NSTableCellView alloc] init];
        cell.identifier = column.identifier;
        NSTextField *text = [NSTextField labelWithString:@""];
        text.lineBreakMode = NSLineBreakByTruncatingTail;
        text.translatesAutoresizingMaskIntoConstraints = NO;
        [cell addSubview:text];
        cell.textField = text;
        [text.leadingAnchor constraintEqualToAnchor:cell.leadingAnchor constant:2].active = YES;
        [text.trailingAnchor constraintEqualToAnchor:cell.trailingAnchor constant:-2].active = YES;
        [text.centerYAnchor constraintEqualToAnchor:cell.centerYAnchor].active = YES;
    }
    NSString *value = @"";
    if (table == self.games)
    {
        const VertrixGame *game = &vertrix_games[row];
        if ([column.identifier isEqualToString:@"Game"])
        {
            value = @(game->title);
            cell.textField.font = [NSFont boldSystemFontOfSize:13];
        }
        else if ([column.identifier isEqualToString:@"Year"])
        {
            value = @(game->year);
        }
        else if ([column.identifier isEqualToString:@"Files"])
        {
            value = [self statusOf:game];
            cell.textField.textColor = NSColor.secondaryLabelColor;
        }
        else
        {
            value = @(game->about);
        }
    }
    else
    {
        value = [self currentAlbum].titles[row];
    }
    cell.textField.stringValue = value;
    return cell;
}

@end

/* --- menus --------------------------------------------------------------------------------- */

static NSMenuItem *item(NSString *title, SEL action, NSString *key)
{
    return [[NSMenuItem alloc] initWithTitle:title action:action keyEquivalent:key];
}

static void build_menus(Launcher *launcher)
{
    NSMenu *bar = [[NSMenu alloc] init];
    NSMenu *app = [[NSMenu alloc] initWithTitle:@"Vertrix"];
    [app addItem:item(@"About Vertrix", @selector(orderFrontStandardAboutPanel:), @"")];
    [app addItem:NSMenuItem.separatorItem];
    [app addItem:item(@"Hide Vertrix", @selector(hide:), @"h")];
    NSMenuItem *others = item(@"Hide Others", @selector(hideOtherApplications:), @"h");
    others.keyEquivalentModifierMask = NSEventModifierFlagCommand | NSEventModifierFlagOption;
    [app addItem:others];
    [app addItem:item(@"Show All", @selector(unhideAllApplications:), @"")];
    [app addItem:NSMenuItem.separatorItem];
    [app addItem:item(@"Quit Vertrix", @selector(terminate:), @"q")];

    NSMenu *file = [[NSMenu alloc] initWithTitle:@"File"];
    NSMenuItem *play = item(@"Play", @selector(play:), @"o");
    play.target = launcher;
    [file addItem:play];
    NSMenuItem *show = item(@"Show Vertrix Folder", @selector(showFolder:), @"");
    show.target = launcher;
    [file addItem:show];
    [file addItem:NSMenuItem.separatorItem];
    [file addItem:item(@"Close", @selector(performClose:), @"w")];

    NSMenu *window = [[NSMenu alloc] initWithTitle:@"Window"];
    [window addItem:item(@"Minimize", @selector(performMiniaturize:), @"m")];
    [window addItem:item(@"Zoom", @selector(performZoom:), @"")];

    for (NSMenu *menu in @[ app, file, window ])
    {
        NSMenuItem *top = [[NSMenuItem alloc] init];
        top.submenu = menu;
        [bar addItem:top];
    }
    NSApp.mainMenu = bar;
    NSApp.windowsMenu = window;
}

int main(int argc, char **argv)
{
    @autoreleasepool
    {
        [NSApplication sharedApplication];
        NSApp.activationPolicy = NSApplicationActivationPolicyRegular;
        Launcher *launcher = [[Launcher alloc] init];
        NSApp.delegate = launcher;
        build_menus(launcher);
        [NSApp run];
    }
    return 0;
}
