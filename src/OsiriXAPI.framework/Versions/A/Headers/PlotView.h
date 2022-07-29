/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <AppKit/AppKit.h>

@class ROI;

/** \brief  Plot View */

@interface PlotView : NSView
{
			float					*dataArray;
			long					dataSize;
			long					curMousePosition;
			ROI						*curROI;
}
- (void)setData:(float*)array :(long) size;
- (void)setCurROI: (ROI*) r;
@end
