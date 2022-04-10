#import "gRPCTaskController.h"
#import "gRPCUtilities.h"

@implementation gRPCTaskController

@synthesize stdOutColor, stdErrColor, backgroundColor, consoleTextColor;

- (id)init
{
    self = [super initWithWindowNibName:@"gRPCTaskWindow"];
    if (!self) {
        gRPCLogError(@"Could not initialize task controller");
        return  nil;
    }
    stdOutColor = [NSColor greenColor];
    stdErrColor = [NSColor redColor];
    consoleTextColor = [NSColor whiteColor];
    backgroundColor = [NSColor blackColor];
    
    return self;
}

- (void)windowDidLoad
{
    [[self window] setLevel: NSStatusWindowLevel];
    [textView setEditable:NO];
    [textView setDrawsBackground:YES];
    [textView setBackgroundColor:backgroundColor];
    [infoLabel setStringValue:@""];
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

- (NSString *)currentTimeString
{
    NSDate *currDate = [NSDate date];
    NSDateFormatter* dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setDateFormat:@"[dd/MM/YY - HH:mm:ss]"];
    NSString* dateString = [dateFormatter stringFromDate:currDate];
    [dateFormatter release];
    return dateString;
}

- (void) stdOutDataAvailable:(id) sender
{
    NSFileHandle *fileHandle = (NSFileHandle *)[sender object];
    NSData *data = [fileHandle availableData];
    if ([data length] > 0)
    {
        [self appendTextToView:[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] withColor:stdOutColor];
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
        [self appendTextToView:[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] withColor:stdErrColor];
        [fileHandle waitForDataInBackgroundAndNotify];
    }
    else
    {
        gRPCLogError(@"EOF for handle");
    }
}

- (void) taskTerminated:(id) sender
{
    [self appendTextToView:[NSString stringWithFormat:@"Task finished: %@\n\n", [self currentTimeString]] withColor:consoleTextColor];
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) runScript:(gRPCScript *)script
{
    // Get all relevant paramters from the script object
    NSURL *scriptURL = [script url];
    NSURL *interpreterURL = [script interpreter];
    BOOL blocking = [script blocking];
    NSURL *scriptDirectoryURL = [scriptURL URLByDeletingLastPathComponent];
    
    // Set up a task and pipe for stderr/stdout
    NSTask *task = [[[NSTask alloc] init] autorelease];
    NSPipe *pipeStdErr = [[[NSPipe alloc] init] autorelease];
    NSPipe *pipeStdOut = [[[NSPipe alloc] init] autorelease];
    
    // Set task variables
    [task setExecutableURL:interpreterURL];
    if ([script language] == gRPCPython)
    {
        [task setArguments:@[@"-u", [scriptURL path]]]; // Don't buffer stdout/stderr
    }
    else
    {
        [task setArguments:@[[scriptURL path]]];
    }
    [task setCurrentDirectoryURL:scriptDirectoryURL];
    [task setStandardOutput:pipeStdOut];
    [task setStandardError:pipeStdErr];
    
    // Set up the stdout to print to screen
    NSFileHandle *fileHandleStdOut = [pipeStdOut fileHandleForReading];
    [fileHandleStdOut waitForDataInBackgroundAndNotify];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stdOutDataAvailable:) name:NSFileHandleDataAvailableNotification object:fileHandleStdOut];
    
    // Set up the stderr to print to screen
    NSFileHandle *fileHandleStdErr = [pipeStdErr fileHandleForReading];
    [fileHandleStdErr waitForDataInBackgroundAndNotify];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(stdErrDataAvailable:) name:NSFileHandleDataAvailableNotification object:fileHandleStdErr];
    
    // Listen for when the task terminates
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(taskTerminated:) name:NSTaskDidTerminateNotification object:task];
    
    // Clear the previous stdout - is this a good feature?
    [textView setString:@""];
    
    // Launch the task and wait if required.
    [task launch];
    
    // Append text to the view so we know this is a new session
    
    [self appendTextToView:[NSString stringWithFormat:@"Starting task with file: %@\n%@\n", [scriptURL path], [self currentTimeString]] withColor:consoleTextColor];

    
    if (blocking)
    {
        [task waitUntilExit];
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
