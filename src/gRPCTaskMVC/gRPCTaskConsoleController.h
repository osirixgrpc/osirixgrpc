#import <Cocoa/Cocoa.h>

#import "gRPCScript.h"

NS_ASSUME_NONNULL_BEGIN

@interface gRPCTaskConsoleController : NSWindowController
{
    IBOutlet NSTextView *textView;
    IBOutlet NSTextField *infoLabel;
}

@property (retain, nonatomic) NSColor * consoleStdOutColor;
@property (retain, nonatomic) NSColor * consoleStdErrColor;
@property (retain, nonatomic) NSColor * consoleTextColor;
@property (retain, nonatomic) NSColor * consoleBackgroundColor;

- (void)runScript:(gRPCScript *)script;

- (IBAction)clearPushed:(id)sender;
- (IBAction)savePushed:(id)sender;

@end

NS_ASSUME_NONNULL_END
