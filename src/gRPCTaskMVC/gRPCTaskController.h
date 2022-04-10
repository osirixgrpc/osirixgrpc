#import <Cocoa/Cocoa.h>

#import "gRPCScript.h"

NS_ASSUME_NONNULL_BEGIN

@interface gRPCTaskController : NSWindowController
{
    IBOutlet NSTextView *textView;
    IBOutlet NSTextField *infoLabel;
}

@property (retain, nonatomic) NSColor * textColor;

- (void)runScript:(gRPCScript *)script;

- (IBAction)clearPushed:(id)sender;
- (IBAction)savePushed:(id)sender;

@end

NS_ASSUME_NONNULL_END
