/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "ViewerController.h"
#import "OrthogonalReslice.h"
@class OrthogonalMPRView;

/** \brief  Controller for Orthogonal MPR */

@interface OrthogonalMPRController : NSObject { //NSWindowController {
	NSMutableArray				*originalDCMPixList, *xReslicedDCMPixList, *yReslicedDCMPixList, *originalDCMFilesList, *originalROIList;
	OrthogonalReslice			*reslicer;
	float						sign;
	
	float						originalCrossPositionX, originalCrossPositionY, xReslicedCrossPositionX, xReslicedCrossPositionY, yReslicedCrossPositionX, yReslicedCrossPositionY;
	long						orientationVector;
    
	IBOutlet OrthogonalMPRView	*originalView, *xReslicedView, *yReslicedView;

	id							viewer;
	NSRect						originalViewFrame, xReslicedViewFrame, yReslicedViewFrame;
	
	short						thickSlabMode, thickSlab;
	
	NSData						*transferFunction;
	
	ViewerController			*viewerController;
    
    BOOL                        saveROIsTo2DViewer;
}

@property long orientationVector;
@property (readonly) ViewerController *viewerController;
 
- (id) initWithPixList: (NSArray*) pixList :(NSArray*) filesList :(NSData*) vData :(ViewerController*) vC :(ViewerController*) bC :(id) newViewer;
- (id) initWithPixList: (NSArray*)pix :(NSArray*)files :(NSData*)vData :(ViewerController*)vC :(ViewerController*)bC :(id)newViewer copyROI: (BOOL) copyROI;

- (void) setPixList: (NSArray*)pix :(NSArray*)files :(ViewerController*)vC;
- (void) setPixList: (NSArray*)pix :(NSArray*)files :(ViewerController*)vC copyROI: (BOOL) copyROI;

- (void) reslice: (long) x : (long) y : (OrthogonalMPRView*) sender;
- (void) flipVolume;

- (void) ApplyCLUTString:(NSString*) str;
- (void) ApplyOpacityString:(NSString*) str;

- (void) setWLWW:(float) iwl :(float) iww;
- (void) setCurWLWWMenu:(NSString*) str;
- (void) setFusion;

- (short) thickSlabMode;
- (void) setThickSlabMode : (short) newThickSlabMode;
- (short) thickSlab;
- (long) maxThickSlab;
- (float) thickSlabDistance;
- (void) setThickSlab : (short) newThickSlab;

- (void) showViews:(id)sender;
- (void) setTransferFunction:(NSData*) tf;

- (OrthogonalReslice*) reslicer;
- (void)setReslicer:(OrthogonalReslice*)newReslicer;
- (OrthogonalMPRView*) originalView;
- (OrthogonalMPRView*) xReslicedView;
- (OrthogonalMPRView*) yReslicedView;
- (NSMutableArray*) originalDCMFilesList;
- (void) setCrossPosition: (float) x : (float) y : (id) sender;
- (void) setBlendingFactor:(float) f;
- (id) viewer;
- (float) sign;

- (void) notifyPositionChange;
- (void) moveToRelativePosition:(NSArray*) relativeDicomLocation;
- (void) moveToAbsolutePosition:(NSArray*) newDicomLocation;

// Tools Selection
- (void) setCurrentTool:(ToolMode) newTool;
- (ToolMode) currentTool;

- (void) saveViewsFrame;
- (void) saveScaleValue;
- (void) displayResliceAxes: (long) boo;
- (void) restoreScaleValue;
- (void) restoreViewsFrame;
- (void) toggleDisplayResliceAxes: (id) sender;
- (void) resetImage;
- (void) saveROIsTo2DViewer;

- (NSMutableArray*) originalDCMPixList;
- (void) scaleToFit : (id) destination;
- (void) scaleToFit;
- (void) setScaleValue:(float) x;
- (void) fullWindowView: (id) sender;
- (void) saveCrossPositions;
- (void) restoreCrossPositions;
- (void) scrollTool: (long) from : (long) to : (id) sender;
- (void) doubleClick:(NSEvent *)event :(id) sender;
-(void) refreshViews;

- (void) blendingPropagateOriginal:(OrthogonalMPRView*) sender;
- (void) blendingPropagateX:(OrthogonalMPRView*) sender;
- (void) blendingPropagateY:(OrthogonalMPRView*) sender;
- (void) blendingPropagate:(OrthogonalMPRView*) sender;

- (void) loadROIonXReslicedView: (long) y;
- (void) loadROIonYReslicedView: (long) x;
- (void) loadROIonReslicedViews: (long) x : (long) y;

- (NSMutableArray*) pointsROIAtX: (long) x;
- (NSMutableArray*) pointsROIAtY: (long) y;

- (NSMenu *)contextualMenu;
- (DCMPix*) firtsDCMPixInOriginalDCMPixList;
- (IBAction) flipVertical: (id)sender;
- (IBAction) flipHorizontal: (id)sender;

@end
