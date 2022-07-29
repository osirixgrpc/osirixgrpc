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
#import "N3Geometry.h"

@class ROI;
@class N3MutableBezierPath;
@class OSIFloatVolumeData;

// for now implement closed poly first

@interface OSIPlanarPathROI : OSIROI {
	ROI *_osiriXROI;
	
	N3MutableBezierPath *_bezierPath;
	N3Plane _plane;
}

- (OSIROIMask *)ROIMaskForFloatVolumeData:(OSIFloatVolumeData *)floatVolume; // for this class the passed floatVolume's z direction needs to be perpendicular to the plane 


@end
