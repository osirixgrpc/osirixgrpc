/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "OSIROI.h"
#import "OSIPlanarPathROI.h"
#import "OSIPlanarBrushROI.h"
#import "N3Geometry.h"

@class ROI;
@class OSIFloatVolumeData;

@interface OSIROI (Private)

+ (id)ROIWithOsiriXROI:(ROI *)roi pixToDICOMTransfrom:(N3AffineTransform)pixToDICOMTransfrom homeFloatVolumeData:(OSIFloatVolumeData *)floatVolumeData;
+ (id)ROICoalescedWithSourceROIs:(NSArray *)rois homeFloatVolumeData:(OSIFloatVolumeData *)floatVolumeData;

@end

@interface OSIPlanarPathROI (Private)

- (id)initWithOsiriXROI:(ROI *)roi pixToDICOMTransfrom:(N3AffineTransform)pixToDICOMTransfrom homeFloatVolumeData:(OSIFloatVolumeData *)floatVolumeData;

@end

@interface OSIPlanarBrushROI (Private)

- (id)initWithOsiriXROI:(ROI *)roi pixToDICOMTransfrom:(N3AffineTransform)pixToDICOMTransfrom homeFloatVolumeData:(OSIFloatVolumeData *)floatVolumeData;

@end
