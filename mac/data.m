#import <Cocoa/Cocoa.h>

#include "data.h"

#include <stdlib.h>

const char *vertrix_home(void)
{
    static char path[1024];
    if (!path[0])
    {
        NSString *home = NSProcessInfo.processInfo.environment[@"VERTRIX_HOME"];
        if (home.length == 0)
        {
            NSURL *support =
                [NSFileManager.defaultManager URLsForDirectory:NSApplicationSupportDirectory
                                                     inDomains:NSUserDomainMask]
                    .firstObject;
            home = [support.path stringByAppendingPathComponent:@"Vertrix"];
        }
        [NSFileManager.defaultManager createDirectoryAtPath:home
                                withIntermediateDirectories:YES
                                                 attributes:nil
                                                      error:nil];
        snprintf(path, sizeof path, "%s", home.fileSystemRepresentation);
    }
    return path;
}

const char *vertrix_game_folder(const VertrixGame *game)
{
    static char paths[VERTRIX_GAMES][1024];
    char *path = paths[game - vertrix_games];
    snprintf(path, sizeof paths[0], "%s/%s", vertrix_home(), game->folder);
    [NSFileManager.defaultManager createDirectoryAtPath:@(path)
                            withIntermediateDirectories:YES
                                             attributes:nil
                                                  error:nil];
    return path;
}

/* The entry of `directory` named `name` in any case, or nil. */
static NSString *find_name(NSString *directory, NSString *name)
{
    for (NSString *entry in [NSFileManager.defaultManager contentsOfDirectoryAtPath:directory
                                                                              error:nil])
    {
        if ([entry caseInsensitiveCompare:name] == NSOrderedSame)
        {
            return [directory stringByAppendingPathComponent:entry];
        }
    }
    return nil;
}

int vertrix_game_ready(const VertrixGame *game, const char *folder)
{
    return find_name(@(folder), @(game->needs)) != nil;
}

/* Copies `source` to `target`, replacing it. */
static BOOL copy_over(NSString *source, NSString *target, NSError **error)
{
    NSFileManager *files = NSFileManager.defaultManager;
    NSString *old = find_name(target.stringByDeletingLastPathComponent, target.lastPathComponent);
    if (old)
    {
        [files removeItemAtPath:old error:nil];
    }
    return [files copyItemAtPath:source toPath:target error:error];
}

/* The game's files from `source` (the folder that holds what it needs) into `folder`: the whole
 * release, or only the archive, under the name the game opens. */
static BOOL import_from(const VertrixGame *game, NSString *source, const char *folder,
                        NSError **error)
{
    NSString *target = @(folder);
    if (!game->whole_release)
    {
        NSString *archive = find_name(source, @(game->needs));
        return archive &&
               copy_over(archive, [target stringByAppendingPathComponent:@(game->needs)], error);
    }
    for (NSString *entry in [NSFileManager.defaultManager contentsOfDirectoryAtPath:source
                                                                              error:error])
    {
        if ([entry hasPrefix:@"."])
        {
            continue;
        }
        if (!copy_over([source stringByAppendingPathComponent:entry],
                       [target stringByAppendingPathComponent:entry], error))
        {
            return NO;
        }
    }
    return YES;
}

/* Where a build keeps its copy: the app's own Resources/Data, or, for a game inside
 * Vertrix.app/Contents/Helpers, Vertrix.app's. */
static NSArray<NSString *> *bundled_folders(const VertrixGame *game)
{
    NSString *own = NSBundle.mainBundle.resourcePath;
    NSString *outer = [[NSBundle.mainBundle.bundlePath stringByDeletingLastPathComponent]
        stringByDeletingLastPathComponent];
    NSString *name = [@"Data" stringByAppendingPathComponent:@(game->folder)];
    return @[
        [own stringByAppendingPathComponent:name],
        [[outer stringByAppendingPathComponent:@"Resources"] stringByAppendingPathComponent:name]
    ];
}

int vertrix_import_bundled(const VertrixGame *game, const char *folder)
{
    for (NSString *source in bundled_folders(game))
    {
        if (find_name(source, @(game->needs)) && import_from(game, source, folder, nil))
        {
            return vertrix_game_ready(game, folder);
        }
    }
    return 0;
}

/* The folder under `path` that holds what the game needs: `path` itself, the folder of a chosen
 * file, or a folder one or two levels in (an installation's own folders). */
static NSString *source_for(const VertrixGame *game, NSString *path)
{
    BOOL directory = NO;
    [NSFileManager.defaultManager fileExistsAtPath:path isDirectory:&directory];
    if (!directory)
    {
        path = path.stringByDeletingLastPathComponent;
    }
    NSString *needs = @(game->needs);
    if (find_name(path, needs))
    {
        return path;
    }
    NSDirectoryEnumerator *walk = [NSFileManager.defaultManager enumeratorAtPath:path];
    for (NSString *entry in walk)
    {
        if (walk.level > 3)
        {
            [walk skipDescendants];
            continue;
        }
        if ([entry.lastPathComponent caseInsensitiveCompare:needs] == NSOrderedSame)
        {
            return [path stringByAppendingPathComponent:entry.stringByDeletingLastPathComponent];
        }
    }
    return nil;
}

int vertrix_import_ask(const VertrixGame *game, const char *folder)
{
    for (;;)
    {
        NSOpenPanel *panel = [NSOpenPanel openPanel];
        panel.canChooseFiles = YES;
        panel.canChooseDirectories = YES;
        panel.allowsMultipleSelection = NO;
        panel.title = [NSString stringWithFormat:@"%s", game->title];
        panel.message = [NSString
            stringWithFormat:@"Choose %s, or the folder that holds it.", game->needs_text];
        panel.prompt = @"Copy";
        if ([panel runModal] != NSModalResponseOK)
        {
            return 0;
        }
        NSString *source = source_for(game, panel.URL.path);
        NSError *error = nil;
        if (source && import_from(game, source, folder, &error) && vertrix_game_ready(game, folder))
        {
            return 1;
        }
        NSAlert *alert = [[NSAlert alloc] init];
        alert.messageText = [NSString stringWithFormat:@"%s needs %s.", game->title, game->needs];
        alert.informativeText =
            error ? error.localizedDescription
                  : [NSString stringWithFormat:@"There is no %s there. Choose %s.", game->needs,
                                               game->needs_text];
        [alert addButtonWithTitle:@"Choose Again"];
        [alert addButtonWithTitle:@"Cancel"];
        if ([alert runModal] != NSAlertFirstButtonReturn)
        {
            return 0;
        }
    }
}
