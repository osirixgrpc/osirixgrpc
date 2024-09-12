#import <Cocoa/Cocoa.h>

#import "gRPCTaskController.h"

@interface gRPCToolbarController : NSViewController
{
    IBOutlet NSView * popUpButtonViewViewerController;
    IBOutlet NSPopUpButton * popUpButtonViewerController;
    IBOutlet NSView * popUpButtonViewBrowserController;
    IBOutlet NSPopUpButton * popUpButtonBrowserController;
    IBOutlet NSView * popUpButtonViewVRController;
    IBOutlet NSPopUpButton * popUpButtonVRController;
    
    gRPCTaskController *taskController;
}

-(id) initWithTaskController:(gRPCTaskController *) taskController_;

+ (NSString *) viewerControllerToolbarID;
+ (NSString *) browserControllerToolbarID;
+ (NSString *) vrControllerToolbarID;

- (NSToolbarItem *) toolbarItemForViewerController;
- (NSToolbarItem *) toolbarItemForBrowserController;
- (NSToolbarItem *) toolbarItemForVRController;

@end
