/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <AppKit/AppKit.h>
#import "ROI.h"
#import "MyNSTextView.h"
#import "ViewerController.h"

/** \brief Window Controller for ROI */

@interface ROIWindow : NSWindowController <NSComboBoxDataSource>
{	
	ROI						*curROI;
	ViewerController		*curController;
    NSWindow                *curWindow;
	
	BOOL					loaded;
	IBOutlet NSButton		*allWithSameName;
	
	IBOutlet NSComboBox		*name;
	IBOutlet MyNSTextView   *comments;
	IBOutlet NSColorWell	*colorButton;
	IBOutlet NSSlider		*thicknessSlider, *opacitySlider;
	NSArray			        *roiNames;
	NSTimer					*getName;
	NSString				*previousName;
}
@property (retain) NSArray* roiNames;

- (IBAction) acceptSheet:(id)sender;
- (id) initWithROI: (ROI*) iroi :(ViewerController*) c;
- (ROI*) curROI;
- (IBAction) setColor:(NSColorWell*) sender;
- (IBAction) setThickness:(NSSlider*) sender;
- (IBAction) setOpacity:(NSSlider*) sender;
- (IBAction) setTextData:(id) sender;
- (void) setROI: (ROI*) iroi :(ViewerController*) c;
- (BOOL) allWithSameName;
- (void) windowWillClose:(NSNotification *)notification;

@end
