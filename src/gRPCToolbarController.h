#import <Cocoa/Cocoa.h>

@interface gRPCToolbarController : NSViewController
{
    IBOutlet NSView * popUpButtonViewViewerController;
    IBOutlet NSPopUpButton * popUpButtonViewerController;
    IBOutlet NSView * popUpButtonViewBrowserController;
    IBOutlet NSPopUpButton * popUpButtonBrowserController;
    IBOutlet NSView * popUpButtonViewVRController;
    IBOutlet NSPopUpButton * popUpButtonVRController;
    
    NSMutableArray *tasks;
}

+ (NSString *) viewerControllerToolbarID;
+ (NSString *) browserControllerToolbarID;
+ (NSString *) vrControllerToolbarID;

- (NSToolbarItem *) toolbarItemForViewerController;
- (NSToolbarItem *) toolbarItemForBrowserController;
- (NSToolbarItem *) toolbarItemForVRController;

@end
