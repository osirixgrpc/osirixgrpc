/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "OSIROI.h"
#import "OSIROIMask.h"

@interface OSIMaskROI : OSIROI
{
    OSIROIMask *_mask;
    NSString *_name;
    NSColor *_fillColor;
    
    OSISlab _cachedSlab;
    N3AffineTransform _cachedDicomToPixTransform;
    N3Vector _cachedMinCorner;
    NSData *_cachedMaskRunsData;
}

- (id)initWithROIMask:(OSIROIMask *)mask homeFloatVolumeData:(OSIFloatVolumeData *)floatVolumeData name:(NSString *)name;

@property (nonatomic, readonly, retain) OSIROIMask *mask;

@end
