/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "OSIROI.h"
#import "OSIGeometry.h"

@class OSIVolumeData;
@class ROI;

@interface OSIPlanarBrushROI : OSIROI
{
    ROI *_osiriXROI;
    
    OSIFloatVolumeData *_brushMask;
    N3Plane _plane;
    NSArray *_convexHull;
}
@end
