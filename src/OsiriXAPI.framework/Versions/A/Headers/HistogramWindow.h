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
#import "HistoView.h"

#define HISTOSIZE 512

/** \brief Window Controller for histogram display */

@interface HistoWindow : NSWindowController {
	
	ROI						*curROI;
	
	float					*data, histoData[ HISTOSIZE], maxValue, minValue;
	long					dataSize;
	
	IBOutlet HistoView		*histo;
	IBOutlet NSSlider		*binSlider;
	IBOutlet NSTextField	*binText, *maxText;
}

- (id) initWithROI: (ROI*) iroi;
- (id) initWithData: (float*) d size:(unsigned long) s pix: (DCMPix*) p;
- (ROI*) curROI;
- (IBAction) changeBin: (id) sender;
@end
