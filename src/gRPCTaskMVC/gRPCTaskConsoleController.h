#import <Cocoa/Cocoa.h>

@interface gRPCTaskConsoleController : NSWindowController
{
    IBOutlet NSTextView *textView;
    IBOutlet NSTextField *infoLabel;
}

@property (retain, nonatomic) NSColor * consoleStdOutColor;
@property (retain, nonatomic) NSColor * consoleStdErrColor;
@property (retain, nonatomic) NSColor * consoleTextColor;
@property (retain, nonatomic) NSColor * consoleBackgroundColor;

- (IBAction)clearPushed:(id)sender;
- (IBAction)savePushed:(id)sender;

- (void) stdOutDataAvailable:(id) sender;
- (void) stdErrDataAvailable:(id) sender;

- (void) appendTextToView: (NSString *)text;

@end
