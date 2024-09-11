#import <Cocoa/Cocoa.h>

#import "gRPCScriptController.h"
#import "gRPCTaskConsoleController.h"

@interface gRPCToolbarController : NSViewController
{
    IBOutlet NSView * popUpButtonViewViewerController;
    IBOutlet NSPopUpButton * popUpButtonViewerController;
    IBOutlet NSView * popUpButtonViewBrowserController;
    IBOutlet NSPopUpButton * popUpButtonBrowserController;
    IBOutlet NSView * popUpButtonViewVRController;
    IBOutlet NSPopUpButton * popUpButtonVRController;
    
    gRPCScriptController *scriptController;
    gRPCTaskConsoleController *taskConsoleController;
}

-(id) initWithScriptController:(gRPCScriptController *) scriptController_ andTaskController:(gRPCTaskConsoleController *) taskConsoleController_;

+ (NSString *) viewerControllerToolbarID;
+ (NSString *) browserControllerToolbarID;
+ (NSString *) vrControllerToolbarID;

- (NSToolbarItem *) toolbarItemForViewerController;
- (NSToolbarItem *) toolbarItemForBrowserController;
- (NSToolbarItem *) toolbarItemForVRController;

@end
