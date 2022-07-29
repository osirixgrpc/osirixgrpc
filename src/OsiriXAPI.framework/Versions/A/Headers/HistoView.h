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

/** \brief  View for histogram display */

@interface HistoView : NSView
{
        float					*dataArray;
		long					dataSize, bin, curMousePosition, pixels, minV, maxV;
        float					maxValue;
		DCMPix					*curPix;
		NSColor					*backgroundColor, *binColor, *selectedBinColor, *textColor, *borderColor;
}
- (void)setData:(float*)array :(long) size :(long) b;
- (void)setMaxValue:(float)value :(long) pixels;
- (void)setCurROI: (ROI*) r;
- (void)setCurPix: (DCMPix*) r;
- (void)setRange:(long) mi :(long) max;

- (NSColor*)backgroundColor;
- (NSColor*)binColor;
- (NSColor*)selectedBinColor;
- (NSColor*)textColor;
- (NSColor*)borderColor;

- (void)setBackgroundColor:(NSColor*)aColor;
- (void)setBinColor:(NSColor*)aColor;
- (void)setSelectedBinColor:(NSColor*)aColor;
- (void)setTextColor:(NSColor*)aColor;
- (void)setBorderColor:(NSColor*)aColor;

@end
