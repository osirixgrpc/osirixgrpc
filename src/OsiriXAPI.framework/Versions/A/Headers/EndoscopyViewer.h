/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>
#import "OrthogonalMPRController.h"
#import "VRController.h"
#import "EndoscopyVRController.h"
#import "Camera.h"
#import "Window3DController.h"
#import "FlyAssistant.h"

@class OSIVoxel;

/** \brief   Window Controller for Endoscopy
*/


@interface EndoscopyViewer : Window3DController <NSToolbarDelegate, NSWindowDelegate, NSSplitViewDelegate>
{
	IBOutlet OrthogonalMPRController	*mprController;
	IBOutlet EndoscopyVRController		*vrController;
	NSMutableArray						*pixList;
	
	IBOutlet NSSplitView				*topSplitView, *bottomSplitView, *horizontalSplit;
	
	NSToolbar							*toolbar;
    IBOutlet NSView						*tools3DView, *tools2DView, *engineView, *shadingView, *LODView;
	IBOutlet NSMatrix					*tools3DMatrix, *tools2DMatrix;
	
	IBOutlet NSView						*WLWW3DView, *WLWW2DView;
	IBOutlet NSPopUpButton				*wlww2DPopup, *clut2DPopup;
	
	NSString							*cur2DWLWWMenu, *cur2DCLUTMenu;
	
	IBOutlet NSWindow					*exportDCMWindow;
	IBOutlet NSMatrix					*exportDCMViewsChoice;
	IBOutlet NSTextField				*exportDCMSeriesName;
	
	BOOL								exportAllViews;
    BOOL                                dontChangeMPRPosition;
	
    float lodDisplayed;
    int engine;
	
	// Fly assistant
	FlyAssistant* assistant;
	NSMutableArray* centerline;
	NSMutableArray* centerlineAxial, *centerlineCoronal, *centerlineSagittal;
	Point3D*   pointA, *pointB;
	float* assistantInputData;
	int flyAssistantMode;
	BOOL isFlyPathLocked;
	int flyAssistantPositionIndex;
	float centerlineResampleStepLength;
	BOOL lockCameraFocusOnPath;
	BOOL isShowCenterLine;
	BOOL isLookingBackwards;
	
	// Path Assistant
	IBOutlet NSPanel *pathAssistantPanel;
	IBOutlet NSButton *pathAssistantBasicModeButton;
	IBOutlet NSButton *pathAssistantSetPointAButton;
	IBOutlet NSButton *pathAssistantSetPointBButton;
	IBOutlet NSButton *pathAssistantLookBackButton;
	IBOutlet NSMatrix *pathAssistantCameraOrFocalOnPathMatrix;
	IBOutlet NSButton *pathAssistantExportToFlyThruButton;
	
	// assistant advanced settings
	IBOutlet NSPanel *assistantSettingPanel;
	IBOutlet NSTextField *assistantPanelTextThreshold;
	IBOutlet NSTextField *assistantPanelTextResampleSize;
	IBOutlet NSTextField *assistantPanelTextStepLength;
	IBOutlet NSSlider *assistantPanelSliderThreshold;
	IBOutlet NSSlider *assistantPanelSliderResampleSize;
	IBOutlet NSSlider *assistantPanelSliderStepLength;
}


@property(readonly) EndoscopyVRController *vrController;
@property float lodDisplayed;
@property int engine;
@property BOOL dontChangeMPRPosition;

- (id) initWithPixList: (NSMutableArray*) pix :(NSArray*) files :(NSData*) vData :(ViewerController*) bC : (ViewerController*) vC;
- (BOOL) is2DViewer;
- (NSMutableArray*) pixList;
//- (IBAction) centerline: (id) sender;
- (void) setCameraRepresentation: (NSNotification*) note;
- (void) setCameraRepresentation;
- (void) setCameraPositionRepresentation: (Camera*) aCamera;
- (void) setCameraFocalPointRepresentation: (Camera*) aCamera;
- (void) setCameraViewUpRepresentation: (Camera*) aCamera;
- (void) setCamera;
- (void) setupToolbar;
- (void) Apply2DCLUT:(id) sender;
- (void) setCameraPosition:(OSIVoxel *)position  focalPoint:(OSIVoxel *)focalPoint;


#pragma mark-
#pragma mark VR Viewer methods
- (void) ApplyWLWW:(id) sender;

#pragma mark-
#pragma mark Tools Selection
- (IBAction) change2DTool:(id) sender;
- (IBAction) change3DTool:(id) sender;
#pragma mark-
#pragma mark export
- (IBAction) setExportAllViews: (id) sender;
- (BOOL) exportAllViews;
- (IBAction) endDCMExportSettings:(id) sender;
- (unsigned char*) getRawPixels:(long*) width :(long*) height :(long*) spp :(long*) bpp;
#pragma mark-
#pragma mark path assistant
- (IBAction)showPathAssistantPanel:(id)sender;
- (IBAction)pathAssistantSetPointA:(id)sender;
- (IBAction)pathAssistantSetPointB:(id)sender;
- (IBAction)pathAssistantBasicModeButtonAction:(id)sender;
- (IBAction)pathAssistantChangeMode:(id)sender;
- (IBAction)pathAssistantExportToFlyThru:(id)sender;
#pragma mark-
#pragma mark fly assistant
//assistant
- (void) initFlyAssistant:(NSData*) vData;
- (void) flyThruAssistantGoForward: (NSNotification*)note;
- (void) flyThruAssistantGoBackward: (NSNotification*)note;
- (IBAction) applyNewSettingForFlyAssistant:(id) sender;
- (IBAction) showingAssistantSettings:(id) sender;
- (IBAction) showOrHideCenterlines:(id) sender;
- (IBAction) lookBackwards:(id) sender;
- (IBAction) lockCameraOrFocusOnPath:(id) sender;
- (void) updateCenterlineInMPRViews;
- (void) setCameraAtPosition:(OSIVoxel *)cpos TowardsPosition:(OSIVoxel *)fpos;
@end
