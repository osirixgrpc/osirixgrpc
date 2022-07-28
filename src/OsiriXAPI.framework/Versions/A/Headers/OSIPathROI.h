/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OSIROI.h"

@class ROI;
@class N3MutableBezierPath;

// for now implement closed poly first

@interface OSIPathROI : OSIROI {
	ROI *_osiriXROI;
	
	N3MutableBezierPath *_bezierPath;
}

- (id)initWithOsiriXROI:(ROI *)roi pixToDICOMTransfrom:(N3AffineTransform)pixToDICOMTransfrom;

@end
