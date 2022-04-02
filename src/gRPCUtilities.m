#import "gRPCUtilities.h"

#include <arpa/inet.h>

@implementation gRPCUtilities

+ (BOOL)isValidIPAddress:(nonnull NSString *)ipAddress
{
    // Adapted from https://stackoverflow.com/a/10971521
    const char *utf8 = [ipAddress UTF8String];
    int success;

    struct in_addr dst;
    success = inet_pton(AF_INET, utf8, &dst);
    if (success != 1) {
        struct in6_addr dst6;
        success = inet_pton(AF_INET6, utf8, &dst6);
    }

    return success == 1;
}

+ (NSURL *)selectURLWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles
{
    NSOpenPanel *op = [NSOpenPanel openPanel];
    [op setCanChooseDirectories:allowDirs];
    [op setCanChooseFiles:allowFiles];
    if (@available(macOS 11.0, *)) {
        [op setAllowedContentTypes:[NSArray arrayWithObjects:extension, nil]];
    } else {
        [op setAllowedFileTypes:[NSArray arrayWithObjects:extension, nil]];
    }
    NSModalResponse response = [op runModal];
    if (response == NSModalResponseOK)
    {
        NSURL *url = [[op URLs] objectAtIndex:0];
        return url;
    }
    else
    {
        return nil;
    }
}

+ (NSString *)selectFilePathWithExtension:(nullable NSString *)extension allowingDirectories:(BOOL)allowDirs allowingFiles:(BOOL)allowFiles
{
    NSURL *url = [gRPCUtilities selectURLWithExtension:extension allowingDirectories:allowDirs allowingFiles:allowFiles];
    if (url)
    {
        return [url path];
    }
    return nil;
}

+ (NSString *)readFileContentsAtPath:(NSString *)filePath
{
    NSString* content = [NSString stringWithContentsOfFile:filePath
                                                  encoding:NSUTF8StringEncoding
                                                      error:NULL];
    return content;
}

+ (NSString *)readFileContentsAtURL:(NSURL *)url
{
    NSString* content = [NSString stringWithContentsOfURL:url
                                                  encoding:NSUTF8StringEncoding
                                                      error:NULL];
    return content;
}

+ (NSInteger)alertWithMessageText:(nonnull NSString *)message :(nonnull NSString *)firstButton :(nullable NSString *)secondButton :(nullable NSString *)thirdButton :(nullable NSString *)informativeTextWithFormat, ...
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:message];
    [alert addButtonWithTitle:firstButton];
    if (secondButton)
        [alert addButtonWithTitle:secondButton];
    if (thirdButton)
        [alert addButtonWithTitle:thirdButton];
    if (informativeTextWithFormat)
    {
        va_list args;
        va_start(args, informativeTextWithFormat);
        NSString *infText = [[NSString alloc] initWithFormat:informativeTextWithFormat arguments:args];
        [alert setInformativeText:infText];
        [infText release];
        va_end(args);
    }
    [alert setAlertStyle:NSAlertStyleWarning];
    
    NSInteger response = (NSInteger)[alert runModal];
    [alert release];
    return response;
}

@end
