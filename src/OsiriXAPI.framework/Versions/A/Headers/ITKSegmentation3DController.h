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


/** \brief Segmentation WindowController
*/


@interface ITKSegmentation3DController : NSWindowController {

				ViewerController		*viewer, *resultsViewer;

	// parameters
	IBOutlet	NSBox					*parametersBox;
	IBOutlet	NSMatrix				*growingMode;
	IBOutlet	NSPopUpButton			*algorithmPopup;
				NSPoint					startingPoint;
	IBOutlet	NSTextField				*startingPointWorldPosition, *startingPointPixelPosition, *startingPointValue;
	IBOutlet	NSForm					*params;
	// results
	IBOutlet	NSBox					*resultsBox;
	IBOutlet	NSMatrix				*pixelsSet;
	IBOutlet	NSMatrix				*pixelsValue;
	IBOutlet	NSSlider				*roiResolution;
	IBOutlet	NSTextField				*newName;

	IBOutlet	NSButton				*computeButton;
	
	// Algorithms
				NSArray			*algorithms;
				NSArray			*parameters;
				NSArray			*defaultsParameters;
				NSArray			*urlHelp;
}
+ (id) segmentationControllerForViewer:(ViewerController*) v;

- (IBAction) compute:(id) sender;
- (IBAction) preview:(id) sender;
- (id) initWithViewer:(ViewerController*) v;
- (ViewerController*) viewer;
- (IBAction) changeAlgorithm: (id) sender;
- (void) setNumberOfParameters: (int) n;

- (IBAction) algorithmGetHelp:(id) sender;
- (void) fillAlgorithmPopup;

@end
