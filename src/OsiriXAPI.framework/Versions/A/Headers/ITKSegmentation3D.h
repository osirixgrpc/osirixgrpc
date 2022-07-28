/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/



#import <Cocoa/Cocoa.h>

#ifdef __cplusplus
#define id Id
	#include "itkImage.h"
	#include "itkImportImageFilter.h"
#undef id
#import "ITK.h"
#else
@class ITK;
#endif

@class ViewerController;
@class ROI;
@class DCMPix;

/** \brief ITK based segmentation for region growing
*/
@interface ITKSegmentation3D : NSObject {

	ITK		*itkImage;
	BOOL	_resampledData;
	
}

#ifdef id
#define redefineID
#undef id
#endif

+ (NSArray*) fastGrowingRegionWithVolume: (float*) volume width:(long) w height:(long) h depth:(long) depth seedPoint:(long*) seed from:(float) from pixList:(NSArray*) pixList;
- (id) initWith :(NSArray*) pix :(float*) volumeData  :(long) slice;
- (id) initWithPix :(NSArray*) pix volume:(float*) volumeData  slice:(long) slice resampleData:(BOOL)resampleData;
+ (id) itkSegmentationWithPix: (DCMPix*) p;

- (ROI*) regionGrowing3D:(ViewerController*) srcViewer :(ViewerController*) destViewer :(long) slice :(NSPoint) startingPoint :(int) algorithmNumber :(NSArray*) parameters :(BOOL) setIn :(float) inValue :(BOOL) setOut :(float) outValue :(int) roiType :(long) roiResolution :(NSString*) newname :(BOOL) mergeWithExistingROIs;

- (ROI*) regionGrowing3D:(ViewerController*) srcViewer :(ViewerController*) destViewer :(long) slice :(NSPoint) startingPoint :(int) algorithmNumber :(NSArray*) parameters :(BOOL) setIn :(float) inValue :(BOOL) setOut :(float) outValue :(int) roiType :(long) roiResolution :(NSString*) newname :(BOOL) mergeWithExistingROIs :(ROI*) limit3DBall :(BOOL) outBall;

- (ROI*) regionGrowing3DForViewer:(ViewerController*) srcViewer slice:(long) slice startingPoint:(NSPoint) startingPoint algorithmNumber:(int) algorithmNumber parameters:(NSArray*) parameters   roiName:(NSString*) newname;
- (ROI*) regionGrowing3DForViewer:(ViewerController*) srcViewer slice:(long) slice startingPoint:(NSPoint) startingPoint algorithmNumber:(int) algorithmNumber roiType:(int) roiType roiResolution:(long) roiResolution parameters:(NSArray*) parameters addToROIList:(BOOL) addToROIList;

- (ROI*) regionGrowing3DForViewer:(ViewerController*) srcViewer destinationViewer:(ViewerController*) destViewer slice:(long) slice startingPoint:(NSPoint) startingPoint algorithmNumber:(int) algorithmNumber parameters:(NSArray*) parameters setIn:(BOOL) setIn inValue:(float) inValue setOut:(BOOL) setOut outValue:(float) outValue roiType:(int) roiType roiResolution:(long) roiResolution roiName:(NSString*) newname mergeWithExistingROIs:(BOOL) mergeWithExistingROIs limit3DBall:(ROI*) limit3DBall outBall:(BOOL) outBall;

- (ROI*) regionGrowing2DForPix:(DCMPix*) dcmPix startingPoint:(NSPoint) startingPoint algorithmNumber:(int) algorithmNumber parameters:(NSArray*) parameters roiType:(int) roiType roiResolution:(long) roiResolution roiName:(NSString*) newname;

// extract lumen for Centerline calculation
//- (NSArray *)endoscopySegmentationForViewer:(ViewerController*) srcViewer seeds:(NSArray *)seeds;
+ (NSMutableArray*) extractContour:(unsigned char*) map width:(long) width height:(long) height;
+ (NSMutableArray*) extractContour:(unsigned char*) map width:(long) width height:(long) height numPoints:(long) numPoints;
+ (NSMutableArray*) extractContour:(unsigned char*) map width:(long) width height:(long) height numPoints:(long) numPoints largestRegion:(BOOL) largestRegion;

#ifdef redefineID
#define id Id
#undef redefineID
#endif

@end
