/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@class DicomSeries;

@interface ThumbnailCell : NSButtonCell {
	BOOL rightClick, isStudy;
    BOOL invertedSet, invertedColors;
    
    float animationHeightPercent;
}

@property(readonly) BOOL rightClick;
@property float animationHeightPercent;

+ (float) thumbnailCellWidth;
+ (void) resetThumbnailCellWidth;
+ (BOOL) drawAnnotationsForROIsAndKeyimages: (DicomSeries*) series inRect: (NSRect) imageRect;
+ (BOOL) drawAnnotationsForROIs: (BOOL) imagesWithROIs andKeyimages: (BOOL) imagesWithKeys inRect: (NSRect) imageRect;
+ (void) hasThisObject: (id) object ROIs:(BOOL*)imagesWithROIs orIsKey:(BOOL*)imagesWithKeys;
@end
