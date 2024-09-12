#import "gRPCTaskConsoleController.h"
#import "gRPCUtilities.h"

@implementation gRPCTaskConsoleController

@synthesize consoleStdOutColor, consoleStdErrColor, consoleBackgroundColor, consoleTextColor;

- (id) init
{
    self = [super initWithWindowNibName:@"gRPCTaskConsoleWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize task console");
        return  nil;
    }
    consoleStdOutColor = [NSColor greenColor];
    consoleStdErrColor = [NSColor redColor];
    consoleTextColor = [NSColor whiteColor];
    consoleBackgroundColor = [NSColor blackColor];
    
    [textView setEditable:NO];
    [textView setDrawsBackground:YES];
    [textView setBackgroundColor:consoleBackgroundColor];
    
    return self;
}

- (void) windowDidLoad
{
    [[self window] setLevel: NSStatusWindowLevel];
    [textView displayIfNeeded];
}

- (void) appendTextToView: (NSString *)text withColor:(NSColor *)color
{
    int start = (int)[[textView textStorage] length];
    int len = (int)[text length];
    [[[textView textStorage] mutableString] appendString:text];
    [textView setTextColor: color range: NSMakeRange(start, len)];
    [textView scrollToEndOfDocument:nil];
    [textView displayIfNeeded];
}

- (void) appendTextToView: (NSString *)text
{
    [self appendTextToView:text withColor:consoleTextColor];
}

- (void) stdOutDataAvailable:(id) sender
{
    NSFileHandle *fileHandle = (NSFileHandle *)[sender object];
    NSData *data = [fileHandle availableData];
    if ([data length] > 0)
    {
        [self appendTextToView:[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] withColor:consoleStdOutColor];
        [fileHandle waitForDataInBackgroundAndNotify];
    }
    else
    {
        gRPCLogError(@"EOF for handle");
    }
}

- (void) stdErrDataAvailable:(id) sender
{
    NSFileHandle *fileHandle = (NSFileHandle *)[sender object];
    NSData *data = [fileHandle availableData];
    if ([data length] > 0)
    {
        [self appendTextToView:[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] withColor:consoleStdErrColor];
        [fileHandle waitForDataInBackgroundAndNotify];
    }
    else
    {
        gRPCLogError(@"EOF for handle");
    }
}

- (IBAction) clearPushed:(id)sender
{
    [textView setString:@""];
}

- (IBAction) savePushed:(id)sender
{
    NSURL *url = [gRPCUtilities saveURLWithTitle:@"Save console output"];
    if (url)
    {
        NSString *contents = [textView string];
        NSError *err;
        BOOL bOK = [contents writeToURL:url atomically:NO encoding:NSUTF8StringEncoding error:&err];
        if (!bOK)
        {
            [infoLabel setStringValue:@"Could not save console"];
            gRPCLogError(@"Could not save console contents to file.  Error: %@", err);
        }
    }
    
}

@end
