/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OSIROIMask.h"
// this is the representation of the data within the generic ROI

/**  
 
 The `OSIROIFloatPixelData` class is used to access pixel in a OSIFloatVolumeData instance data under a given OSIROIMask.
 
 */


@class OSIFloatVolumeData;
@class OSIStudy;

@interface OSIROIFloatPixelData : NSObject {
    NSMutableDictionary *_valueCache;
    NSData *_floatData;
	OSIROIMask *_ROIMask;
	OSIFloatVolumeData *_volumeData;
}

///-----------------------------------
/// @name Creating ROI Float Pixel Data Objects
///-----------------------------------

/** Initializes and returns a newly created ROI Float Pixel Data Object.
 
 Creates a Float Pixel Data instance to access pixels covered by the given mask in the given Float Volume Data
	
 @return The initialized ROI Float Pixel Data object or `nil` if there was a problem initializing the object.
 
 @param roiMask the ROI Mask under which the receiver will access pixels.
 @param volumeData The Float Volume Data the receiver will use to access pixels.
 */

- (id)initWithROIMask:(OSIROIMask *)roiMask floatVolumeData:(OSIFloatVolumeData *)volumeData;

///-----------------------------------
/// @name Accessing Properties
///-----------------------------------

/** The receiver’s mask.
 */
@property (nonatomic, readonly, retain) OSIROIMask *ROIMask;
/** The receiver’s Float Volume Data.
 */
@property (nonatomic, readonly, retain) OSIFloatVolumeData *floatVolumeData;

///-----------------------------------
/// @name Accessing Standard Metrics
///-----------------------------------

/** Returns the mean intensity of the pixels under the mask.
 
 @return The mean intensity of the pixels under the mask
 */
- (float)intensityMean;

/** Returns the maximum intensity of the pixels under the mask.
 
 @return The maximum intensity of the pixels under the mask
 */
- (float)intensityMax;

/** Returns the minumim intensity of the pixels under the mask.
 
 @return The minumim intensity of the pixels under the mask
 */
- (float)intensityMin;

/** Returns the median intensity of the pixels under the mask.
 
 @return The media intensity of the pixels under the mask
 */
- (float)intensityMedian;

/** Returns the interquartile range of the intensity of the pixels under the mask.
 
 @return The interquartile range of the intensity of the pixels under the mask
 */
- (float)intensityInterQuartileRange;

/** Returns the standard deviation of the intensity of the pixels under the mask.
 
 @return The standard deviation of the intensity of the pixels under the mask
 */
- (float)intensityStandardDeviation;

/** Returns by reference the quartiles of the intensity of the pixels under the mask. 
 
 Pass NULL to any parameter you don't care about
 
 */
- (void)getIntensityMinimum:(float *)minimum firstQuartile:(float *)firstQuartile secondQuartile:(float *)secondQuartile thirdQuartile:(float *)thirdQuartile maximum:(float *)maximum;


///-----------------------------------
/// @name Accessing Pixel Data
///-----------------------------------


/** Returns the number of pixels under the mask.
 
 @return The number of pixels under the mask.
 */
- (NSUInteger)floatCount;

/** Copies a number of floats from the start of the receiver's data into a given buffer
 
 This will copy `count * sizeof(float)` bytes into the given buffer.
 
 @return The number of floats copied.
 
 @param buffer A buffer into which to copy data.
 @param count The number of floats to copy.
 */
- (NSUInteger)getFloatData:(float *)buffer floatCount:(NSUInteger)count;

/** Returns a NSData containing the values of the reciever's data
  
 @return a NSData containing the values of the reciever's data.
 
 */
- (NSData *)floatData;


@end
