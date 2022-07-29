/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "N3Geometry.h"
#import "CPRVolumeData.h"

@class CPRVolumeData;

// This operation will fill out floatBytes from the given data. FloatBytes is assumed to be tightly packed float image of width "width" and height "height"
// float bytes will be filled in with values at vectors and each successive scan line will be filled with with values at vector+normal*scanlineNumber
@interface CPRHorizontalFillOperation : NSOperation {
    CPRVolumeData *_volumeData;
    
    float *_floatBytes;
    NSUInteger _width;
    NSUInteger _height;
        
    N3VectorArray _vectors;
    N3VectorArray _normals;
    
    CPRInterpolationMode _interpolationMode;
}

// vectors and normals need to be arrays of length width
- (id)initWithVolumeData:(CPRVolumeData *)volumeData interpolationMode:(CPRInterpolationMode)interpolationMode floatBytes:(float *)floatBytes width:(NSUInteger)width height:(NSUInteger)height vectors:(N3VectorArray)vectors normals:(N3VectorArray)normals;

@property (readonly, retain) CPRVolumeData *volumeData;

@property (readonly, assign) float *floatBytes;
@property (readonly, assign) NSUInteger width;
@property (readonly, assign) NSUInteger height;

@property (readonly, assign) N3VectorArray vectors;
@property (readonly, assign) N3VectorArray normals;

@property (readonly, assign) CPRInterpolationMode interpolationMode; // YES by default

@end
