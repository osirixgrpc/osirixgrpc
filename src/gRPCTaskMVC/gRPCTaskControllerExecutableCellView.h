#import <Cocoa/Cocoa.h>

@interface gRPCTaskControllerExecutableCellView : NSTableCellView
{
    IBOutlet NSButton *openButton;
    IBOutlet NSTextField *textField;
}

@property (readonly) NSButton *openButton;
@property (readwrite, assign) NSTextField *textField;

@end
