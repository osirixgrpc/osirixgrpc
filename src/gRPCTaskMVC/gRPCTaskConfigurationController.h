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
    IBOutlet NSButton *blockingField;
}

@property (retain, nonatomic) gRPCTaskController *delegate;
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *arguments;
@property (nonatomic, copy) NSURL *executable;
@property (nonatomic, assign) gRPCTaskType type;
@property (nonatomic, assign) BOOL blocking;

@end
