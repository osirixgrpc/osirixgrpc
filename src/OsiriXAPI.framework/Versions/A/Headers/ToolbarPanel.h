/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <AppKit/AppKit.h>
#import "ViewerController.h"

/** Window Controller for Toolbar */
@interface ToolbarPanelController : NSWindowController <NSToolbarDelegate, NSWindowDelegate>
{	
	NSToolbar               *toolbar;
	ViewerController		*viewer;
	BOOL					dontReenter;
}

@property (readonly) ViewerController *viewer;

- (long) fixedHeight;
+ (long) hiddenHeight;
- (long) exposedHeight;
+ (long) exposedHeight;
- (id)initForViewer: (ViewerController*) v withToolbar: (NSToolbar*) t;
- (NSToolbar*) toolbar;
+ (void) checkForValidToolbar;
- (void)applicationDidChangeScreenParameters:(NSNotification*)aNotification;

@end
