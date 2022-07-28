/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "NavigatorView.h"
@class ViewerController;
@class DCMView;

/** \brief Window Controller for the Navigator. The Navigator provides a unrolled view of the selected series (in 3D and in 4D).*/
@interface NavigatorWindowController : NSWindowController
{
	ViewerController *viewerController;
    NSData *volumeData; // weak pointer
	IBOutlet NavigatorView *navigatorView;
    IBOutlet NSScrollView *scrollview;
	BOOL dontReEnter;
}

/**  Returns the Navigator Window Controller (which is a unique object).*/
+ (NavigatorWindowController*) navigatorWindowController;
- (void) adjustWindowPosition;
- (id)initWithViewer:(ViewerController*)viewer;
- (void)setViewer:(ViewerController*)viewer;
- (void)initView;
/**  Computes minSize and maxSize of its window.*/
- (void)computeMinAndMaxSize;
- (void)setWindowLevel:(NSNotification*)notification;

@property(readonly) NavigatorView *navigatorView;
@property(readonly) ViewerController *viewerController;

@end
