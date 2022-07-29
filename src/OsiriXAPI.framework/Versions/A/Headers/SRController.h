/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "DCMPix.h"
#import "ColorTransferView.h"
#import "ViewerController.h"
#import "Window3DController.h"

// Fly Thru
#import "FlyThruController.h"
#import "FlyThru.h"
#import "SRFlyThruAdapter.h"

// ROIs Volumes
#define roi3Dvolume

@class SRView;
@class ROIVolume;


/** \brief Window Controller for Surface Rendering */
@interface SRController : Window3DController <NSWindowDelegate, NSToolbarDelegate>
{
    IBOutlet NSView         *toolsView, *LODView, *BlendingView, *export3DView, *perspectiveView, *OrientationsView, *BackgroundColorView;
	IBOutlet SRView			*view;
	IBOutlet NSWindow       *SRSettingsWindow;
    
    BOOL                    fusionSettingsWindow;
    
    NSToolbar				*toolbar;
    NSMutableArray			*pixList;
	NSArray					*fileList;
	
	BOOL					blending;
	NSData					*blendingVolumeData;
    NSMutableArray			*blendingPixList;
	ViewerController		*blendingController;
	
	NSData					*volumeData;
	
	// Fly Thru
	SRFlyThruAdapter		*FTAdapter;
	
	// 3D Points
	ViewerController		*viewer2D;
	NSMutableArray			*roi2DPointsArray, *sliceNumber2DPointsArray, *x2DPointsArray, *y2DPointsArray, *z2DPointsArray;
	
	// ROIs Volumes
	NSMutableArray			*roiVolumes;
	
	float					_firstSurface,  _secondSurface, _resolution, _firstTransparency, _secondTransparency, _decimate;
	int						_smooth;
	NSColor					*_firstColor, *_secondColor;
	BOOL					_shouldDecimate, _shouldSmooth, _useFirstSurface, _useSecondSurface, _shouldRenderFusion;
	
    NSMutableDictionary     *settings, *blendingSettings;
    
	NSTimeInterval			flyThruRecordingTimeFrame;
	
    
    
    
    // Backward compatibility for older xibs, to be delete in next release : not used !
    float                   fusionFirstSurface,  fusionSecondSurface, fusionResolution, fusionFirstTransparency, fusionSecondTransparency, fusionDecimate;
    int                     fusionSmooth;
    NSColor                 *fusionFirstColor, *fusionSecondColor;
    BOOL                    fusionShouldDecimate, fusionShouldSmooth, fusionUseFirstSurface, fusionUseSecondSurface;
    
#ifdef _STEREO_VISION_
	//Added SilvanWidmer 26-08-09
	
	IBOutlet NSWindow       *SRGeometrieSettingsWindow;
	double _screenDistance;
	double _screenHeight;
	double _dolly;
	double _camFocal;
	IBOutlet NSTextField    *distanceValue;
	IBOutlet NSTextField	*heightValue;
	IBOutlet NSTextField    *eyeDistance;
	IBOutlet NSTextField	*camFocalValue;
	IBOutlet NSButton		*parallelFlag;
	IBOutlet NSView        *stereoIconView;
#endif

}

@property float firstSurface, secondSurface, resolution, firstTransparency, secondTransparency, decimate;
@property int smooth;
@property (retain) NSColor *firstColor, *secondColor;
@property BOOL shouldDecimate, shouldSmooth, useFirstSurface, useSecondSurface, shouldRenderFusion;

// Backward compatibility for older xibs, to be delete in next release : not used !
@property float                   fusionFirstSurface,  fusionSecondSurface, fusionResolution, fusionFirstTransparency, fusionSecondTransparency, fusionDecimate;
@property int                     fusionSmooth;
@property (retain) NSColor        *fusionFirstColor, *fusionSecondColor;
@property BOOL                    fusionShouldDecimate, fusionShouldSmooth, fusionUseFirstSurface, fusionUseSecondSurface;


- (IBAction) setOrientation:(id) sender;
- (ViewerController*) blendingController;
- (id) initWithPix:(NSMutableArray*) pix :(NSArray*) f :(NSData*) vData :(ViewerController*) bC :(ViewerController*) vC;
- (id) initWithSTLFile: (NSString*) stlFile series: (DicomSeries*) s;
- (void) setupToolbar;
- (void) setDefaultTool:(id) sender;
- (IBAction) ApplySettings:(id) sender;
- (void) ChangeSettings:(id) sender;
- (IBAction) SettingsPopup:(id) sender;
- (NSArray*) fileList;

- (IBAction)flyThruButtonMenu:(id)sender;
- (IBAction)flyThruControllerInit:(id)sender;
- (void)recordFlyThru;

// 3D Points
- (BOOL) add2DPoint: (float) x : (float) y : (float) z;
- (void) remove2DPoint: (float) x : (float) y : (float) z;
- (void) add3DPoint: (NSNotification*) note;
- (void) remove3DPointROI: (ROI*) removedROI;
- (void) remove3DPoint: (NSNotification*) note;

- (void) createContextualMenu;

- (ViewerController *) viewer2D;
- (void)renderSurfaces;
- (void)renderFusionSurfaces;

#ifdef roi3Dvolume
- (void) computeROIVolumes;
- (NSMutableArray*) roiVolumes;
- (void) displayROIVolume: (ROIVolume*) v;
- (void) hideROIVolume: (ROIVolume*) v;
- (void) displayROIVolumes;
- (IBAction) roiGetManager:(id) sender;
#endif

- (BOOL) shouldRenderFusion;

@end





	
