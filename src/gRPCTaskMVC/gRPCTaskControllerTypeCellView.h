#import <Cocoa/Cocoa.h>

@interface gRPCTaskControllerTypeCellView : NSTableCellView
{
    IBOutlet NSPopUpButton *popUpButton;
}

@property (readonly) NSPopUpButton *popUpButton;

@end
