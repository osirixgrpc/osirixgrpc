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

/** \brief Window Controller for histogram display */

@interface ROI3DSettingsWindow : NSWindowController {
    IBOutlet NSPopover *popoverPeak, *popoverIso;
    NSColor *isoContourColor, *peakValueColor;
    NSNumber *ROI3DDiameterInMm;
    ROI *roi;
}

@property (retain, nonatomic) NSColor *isoContourColor, *peakValueColor;
@property (retain) NSSliderTouchBarItem *isoContourMinTouchBarItem, *isoContourMaxTouchBarItem;
@property (retain) NSNumber *ROI3DDiameterInMm;
@property (retain) ROI *roi;

- (IBAction)togglePopover:(NSButton*)sender;
- (id) initWithROI: (ROI*) r;

-(float) minValueOfSeries;
-(float) maxValueOfSeries;

@end
