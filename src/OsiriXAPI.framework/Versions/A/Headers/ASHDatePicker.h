#import <Cocoa/Cocoa.h>

@protocol ASHDatePickerDelegate;

@class ASHDatePickerController;

@interface ASHDatePicker : NSDatePicker
{
    ASHDatePickerController *controller;
    BOOL showingPopover;
}

@property (nullable, strong, nonatomic) NSPopover *popover;

/**
 * The preferred edge at which to display the popover.
 * Default is NSMaxXEdge.
 */
@property (assign) NSRectEdge preferredPopoverEdge;

@end

@interface ASHDatePickerController : NSViewController

@property (nullable, strong, nonatomic) NSDatePicker *datePicker;

@end
