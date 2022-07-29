/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
@class ViewerController;
@class DCMView;
@class ThreeDPanView;

/** \brief Window Controller for the ThreeDPosition. The ThreeDPosition provides a GUI to move a 3D DataSet in space (3D coordinates).*/
@interface ThreeDPositionController : NSWindowController
{
	ViewerController *viewerController;
	
	IBOutlet ThreeDPanView *axialPan, *verticalPan;
	IBOutlet NSMatrix *matrixMode;
}

+ (ThreeDPositionController*) threeDPositionController;
- (id)initWithViewer:(ViewerController*)viewer;
- (void)setViewer:(ViewerController*)viewer;
- (IBAction) changePosition:(id) sender;
- (void) movePositionPosition:(float*) move;
- (int) mode;
- (IBAction) changeMatrixMode:(id) sender;
- (IBAction) reset:(id) sender;

@property(readonly) ViewerController *viewerController;

@end
