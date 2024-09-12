#import <Cocoa/Cocoa.h>

@interface gRPCTaskControllerBlockingCellView : NSTableCellView

{
    IBOutlet NSButton *checkBox;
}

@property (readonly) NSButton *checkBox;

@end
