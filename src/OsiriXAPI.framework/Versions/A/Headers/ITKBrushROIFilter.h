/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class ROI;

/** \brief Filters brush ROIs
*
*   Filters brush ROI
*   Erode, dilate, open, close
*/

@interface ITKBrushROIFilter : NSObject {

unsigned char *kernelDilate, *kernelErode;
}

// filters
- (void) erode:(ROI*)aROI withStructuringElementRadius:(int)structuringElementRadius;
- (void) dilate:(ROI*)aROI withStructuringElementRadius:(int)structuringElementRadius;
- (void) close:(ROI*)aROI withStructuringElementRadius:(int)structuringElementRadius;
- (void) open:(ROI*)aROI withStructuringElementRadius:(int)structuringElementRadius;

@end
