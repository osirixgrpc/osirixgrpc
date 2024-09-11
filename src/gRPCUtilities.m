#import "gRPCUtilities.h"
#import "gRPCErrorCodes.h"

#include <arpa/inet.h>

@implementation gRPCUtilities

+ (NSInteger)isValidPortNumber:(NSInteger)port
{
    NSInteger validPort = 1;
    if (port < 1024){
        validPort = 0;
    }
    if (port > 65535){
        validPort = 0;
    }
    return validPort;
}

+ (NSInteger)isValidIPAddress:(NSString *)ipAddress
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

    return (NSInteger)success;
}

+ (NSInteger)isPort:(NSInteger) port openAtIPAddress:(NSString *)ipAddress withError:(NSError **)error
{
    // Adapted from https://www.binarytides.com/tcp-connect-port-scanner-c-code-linux-sockets/
    
    if ([gRPCUtilities isValidPortNumber:port] < 1)
    {
        gRPCLogDefault(@"Invalid port number");
        NSDictionary *info = [NSDictionary dictionaryWithObjectsAndKeys:NSLocalizedString(@"Invalid Port Number", nil), NSLocalizedDescriptionKey, nil];
        *error = [NSError errorWithDomain:[gRPCPluginFilter pluginIdentifier] code:gRPCInvalidIPAddress userInfo:info];
        return -1;
    }
    
    if ([gRPCUtilities isValidIPAddress:ipAddress] < 1)
    {
        gRPCLogDefault(@"Invalid IP address");
        NSDictionary *info = [NSDictionary dictionaryWithObjectsAndKeys:NSLocalizedString(@"Invalid IP Address", nil), NSLocalizedDescriptionKey, nil];
        *error = [NSError errorWithDomain:[gRPCPluginFilter pluginIdentifier] code:gRPCInvalidIPAddress userInfo:info];
        return -1;
    }
    
    const char *utf8 = [ipAddress UTF8String];
    
    // Set up the socket information
    struct sockaddr_in sa;
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(utf8);
    sa.sin_port = htons((int) port);
    
    // Create the socket and return an error if not successful
    int sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock < 0)
    {
        NSDictionary *info = [NSDictionary dictionaryWithObjectsAndKeys:NSLocalizedString(@"Socket creation unsuccessful", nil), NSLocalizedDescriptionKey, nil];
        *error = [NSError errorWithDomain:[gRPCPluginFilter pluginIdentifier] code:gRPCSocketError userInfo:info];
        return -1;
    }
    
    // connect to the socket
    NSInteger success = 0;
    int err = connect(sock , (struct sockaddr*)&sa , sizeof sa);
    if (err >= 0)
    {
        success = 1;
    }
    close(sock);
    
    return success;
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

+ (NSURL *)saveURLWithTitle:(nullable NSString *)title
{
    NSSavePanel *savePanel = [NSSavePanel savePanel];
    [savePanel setCanCreateDirectories:YES];
    [savePanel setCanSelectHiddenExtension:YES];
    [savePanel setPrompt:@"save"];
    if (title)
    {
        [savePanel setTitle:title];
    }
    NSModalResponse ok = [savePanel runModal];
    if (ok == NSModalResponseOK)
    {
        NSURL *url = [savePanel URL];
        return url;
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

+ (NSString*)executeBashCommand:(NSString *)command {
    // Create an NSTask to run the provided bash command
    NSTask *task = [[NSTask alloc] init];
    [task setLaunchPath:@"/bin/bash"];
    [task setArguments:@[@"-c", command]];

    // Create a pipe to capture the output of the command
    NSPipe *pipe = [NSPipe pipe];
    [task setStandardOutput:pipe];
    [task setStandardError:pipe]; // Capture both stdout and stderr

    // Launch the task
    [task launch];
    [task waitUntilExit]; // Wait for the task to finish

    // Read the output from the pipe
    NSFileHandle *file = [pipe fileHandleForReading];
    NSData *outputData = [file readDataToEndOfFile];
    NSString *outputString = [[NSString alloc] initWithData:outputData encoding:NSUTF8StringEncoding];

    // Return the output as a string
    return [outputString stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
}

@end
