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
#import "PlotView.h"

/** \brief  Window Controller for Plot */

@interface PlotWindow : NSWindowController {
	
	ROI						*curROI;
	
	float					*data, maxValue, minValue;
	long					dataSize;
	
	IBOutlet PlotView		*plot;
	IBOutlet NSTextField	*maxX, *minY, *maxY, *sizeT;
}

- (id) initWithROI: (ROI*) iroi;
- (ROI*) curROI;
@end
