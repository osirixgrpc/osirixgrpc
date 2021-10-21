#import "gRPCUtilities.h"

@implementation gRPCUtilities

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
