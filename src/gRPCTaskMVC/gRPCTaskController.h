#import <Cocoa/Cocoa.h>

#import "gRPCScript.h"

NS_ASSUME_NONNULL_BEGIN

@interface gRPCTaskController : NSWindowController
{
    IBOutlet NSTextView *textView;
    IBOutlet NSTextField *infoLabel;
}

@property (retain, nonatomic) NSColor * stdOutColor;
@property (retain, nonatomic) NSColor * stdErrColor;
@property (retain, nonatomic) NSColor * consoleTextColor;
@property (retain, nonatomic) NSColor * backgroundColor;

- (void)runScript:(gRPCScript *)script;

- (IBAction)clearPushed:(id)sender;
- (IBAction)savePushed:(id)sender;

@end

NS_ASSUME_NONNULL_END
