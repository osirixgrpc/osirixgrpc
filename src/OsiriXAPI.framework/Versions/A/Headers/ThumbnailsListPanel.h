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

@interface ThumbnailsListPanel : NSWindowController
{	
	NSScrollView            *thumbnailsView;
//    NSView                  *superView;
	long					screen;
	ViewerController		*viewer;
	BOOL					dontReenter;
}

@property (readonly) ViewerController *viewer;

+ (long) fixedWidth;
- (void) setThumbnailsView :(NSScrollView*) tb viewer:(ViewerController*) v;
- (void) thumbnailsListWillClose :(NSScrollView*) tb;
- (id)initForScreen: (long) s;
- (NSView*) thumbnailsView;
+ (void) checkScreenParameters;

@end
