#import <Cocoa/Cocoa.h>

@class gRPCTaskController;

@protocol gRPCTaskConfigurationDelegate <NSObject>
- (void)didPressOK;
- (void)didPressCancel;
@end

@interface gRPCTaskConfigurationController : NSWindowController
{
    IBOutlet NSTextField *nameField;
    IBOutlet NSPathControl *executablePath;
    IBOutlet NSPopUpButton *typeSelection;
    IBOutlet NSTextView *argumentsField;
}

@property (retain, nonatomic) gRPCTaskController *delegate;

@end
