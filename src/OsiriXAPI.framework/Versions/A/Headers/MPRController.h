/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OSIWindowController.h"
#import "MPRDCMView.h"
#import "VRController.h"
#import "VRView.h"
#import "ROI.h"

@class MPRDCMView;

@interface MPRController : Window3DController <NSToolbarDelegate, NSSplitViewDelegate>
{
	// To avoid the Cocoa bindings memory leak bug...
	IBOutlet NSObjectController *ob;
	
	// To be able to use Cocoa bindings with toolbar...
	IBOutlet NSView *tbLOD, *tbThickSlab, *tbWLWW, *tbTools, *tbShading, *tbMovie, *tbBlending, *tbSyncZoomLevel;
	
	NSToolbar *toolbar;
	
	IBOutlet NSMatrix *toolsMatrix;
	IBOutlet NSPopUpButton *popupRoi;
	
	IBOutlet MPRDCMView *mprView1, *mprView2, *mprView3;
	IBOutlet NSSplitView *horizontalSplit, *verticalSplit;
	
	// Blending
	DCMView *blendedMprView1, *blendedMprView2, *blendedMprView3;
	float blendingPercentage;
	int blendingMode;
	BOOL blendingModeAvailable;
	NSString *startingOpacityMenu;
	
	NSMutableArray *undoQueue, *redoQueue;
	
	ViewerController *viewer2D, *fusedViewer2D;
	VRController *hiddenVRController;
	VRView *hiddenVRView;
		
	NSMutableArray *filesList[ MAX4D], *pixList[ MAX4D];
	DCMPix *originalPix;
	NSData *volumeData[ MAX4D];
	BOOL avoidReentry;
	
	// 4D Data support
	NSTimeInterval lastMovieTime;
    NSTimer	*movieTimer;
	int curMovieIndex, maxMovieIndex;
	float movieRate;
	IBOutlet NSSlider *moviePosSlider;
	
	Point3D *mousePosition;
	int mouseViewID;
	
	BOOL displayMousePosition;
	
	// Export Dcm & Quicktime
	IBOutlet NSWindow *dcmWindow;
	IBOutlet NSWindow *quicktimeWindow;
	IBOutlet NSView *dcmSeriesView;
	int dcmFrom, dcmTo, dcmMode, dcmSeriesMode, dcmRotation, dcmRotationDirection, dcmNumberOfFrames, dcmQuality, dcmBatchNumberOfFrames, dcmFormat;
	float dcmInterval, previousDcmInterval;
    float dcmIntervalMin, dcmIntervalMax;
	BOOL dcmSameIntervalAndThickness, dcmBatchReverse;
	NSString *dcmSeriesName;
	MPRDCMView *curExportView;
	BOOL quicktimeExportMode;
	NSMutableArray *qtFileArray;
	
	int dcmmN;
    
    BOOL frameZoomed;
    
	// Clipping Range
	float clippingRangeThickness;
	int clippingRangeMode;
	
	NSArray *wlwwMenuItems;
	
	float LOD;
	BOOL lowLOD;
	
	IBOutlet NSPanel *shadingPanel;
	IBOutlet ShadingArrayController *shadingsPresetsController;
	BOOL shadingEditable;
	IBOutlet NSButton *shadingCheck;
	IBOutlet NSTextField *shadingValues;
	IBOutlet NSView *tbViewsPosition;
	IBOutlet NSView *tbAxisColors;
	NSColor *colorAxis1, *colorAxis2, *colorAxis3;
    NSDictionary *resetDictionary;
    
    NSDictionary *previousPosition;
}

@property (nonatomic) float clippingRangeThickness, dcmInterval, blendingPercentage, dcmIntervalMin, dcmIntervalMax;
@property (nonatomic) int dcmmN, clippingRangeMode, mouseViewID, dcmFrom, dcmTo, dcmMode, dcmSeriesMode, dcmRotation, dcmRotationDirection, dcmNumberOfFrames, dcmQuality, dcmBatchNumberOfFrames;
@property (nonatomic) int dcmFormat, curMovieIndex, maxMovieIndex, blendingMode;
@property (nonatomic, retain) Point3D *mousePosition;
@property (retain) NSArray *wlwwMenuItems;
@property (retain) NSString *dcmSeriesName;
@property (retain) DCMPix *originalPix;
@property (nonatomic) float LOD, movieRate;
@property (nonatomic) BOOL lowLOD, dcmSameIntervalAndThickness, displayMousePosition, blendingModeAvailable, dcmBatchReverse;
@property (nonatomic, retain) NSColor *colorAxis1, *colorAxis2, *colorAxis3;
@property (readonly) MPRDCMView *mprView1, *mprView2, *mprView3;
@property (readonly) NSSplitView *horizontalSplit, *verticalSplit;
@property (retain) NSDictionary *resetDictionary, *previousPosition, *lastSync3DMPRState;
@property BOOL frameZoomed;

@property (retain) NSSliderTouchBarItem *thickSlabSliderTouchBarItem;
@property (retain) NSSliderTouchBarItem *ROIsThicknessSliderTouchBarItem;
@property (retain) NSSliderTouchBarItem *ROIsOpacitySliderTouchBarItem;
@property (retain) NSCustomTouchBarItem *horizontalPanTouchBarItem;
@property CGFloat previousHorizontalTranslationOnTouchBar;

+ (double) angleBetweenVector:(float*) a andPlane:(float*) orientation;

- (id)initWithDCMPixList:(NSMutableArray*)pix filesList:(NSMutableArray*)files volumeData:(NSData*)volume viewerController:(ViewerController*)viewer fusedViewerController:(ViewerController*)fusedViewer;
- (DCMPix*) emptyPix: (DCMPix*) originalPix width: (long) w height: (long) h;
- (MPRDCMView*) selectedView;
- (void) computeCrossReferenceLines:(MPRDCMView*) sender;
- (IBAction)setTool:(id)sender;
- (void) setToolIndex: (int) toolIndex;
- (float) getClippingRangeThicknessInMm;
- (void) propagateWLWW:(MPRDCMView*) sender;
- (void)bringToFrontROI:(ROI*) roi;
- (id) prepareObjectForUndo:(NSString*) string;
- (void)createWLWWMenuItems;
- (void)UpdateWLWWMenu:(NSNotification*)note;
- (void)ApplyWLWW:(id)sender;
- (void)applyWLWWForString:(NSString *)menuString;
- (void) updateViewsAccordingToFrame:(id) sender;
- (void)findShadingPreset:(id) sender;
- (IBAction)editShadingValues:(id) sender;
- (void) moviePlayStop:(id) sender;
- (IBAction) endDCMExportSettings:(id) sender;
- (void) addMoviePixList:(NSMutableArray*) pix :(NSData*) vData __deprecated;
- (void) addMoviePixList:(NSMutableArray*) pix filesList:(NSMutableArray*) files volumeData:(NSData*) vData;
- (void)updateToolbarItems;
- (void)toogleAxisVisibility:(id) sender;
- (BOOL) getMovieDataAvailable;
- (void)Apply3DOpacityString:(NSString*)str;
- (void)Apply2DOpacityString:(NSString*)str;
- (void) setROIToolTag:(ToolMode) roitype;
- (IBAction) roiGetInfo:(id) sender;
- (void) setupToolbar;
- (void) setClippingRangeThicknessInMm:(float) c;
- (void) positionChanged:(MPRDCMView*) sender;
@end
