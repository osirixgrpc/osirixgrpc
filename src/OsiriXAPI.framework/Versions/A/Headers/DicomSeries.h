/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "DCMView.h"

typedef enum {
    noOrientation = 0,
    axialOrientation = 1,
    coronalOrientation = 2,
    sagittalOrientation = 3
} SliceOrientation;

#define THUMBNAILSIZE 160

@class DicomStudy, DicomImage;

/** \brief  Core Data Entity for a Series */

@interface DicomSeries : NSManagedObject
{
	NSNumber	*dicomTime;
    NSImage     *thumbnailImage;
    NSArray     *imagesWithROIsCache, *imagesWithROIsDisplayedInKeyImagesWindowCache;
    int         latestDistantNumberOfImages;
}

@property(nonatomic, retain, readonly) NSNumber* dicomTime;

@property(nonatomic, retain) NSNumber* sortSeriesBySliceLocation;
@property(nonatomic, retain) NSString* comment;
@property(nonatomic, retain) NSString* comment2;
@property(nonatomic, retain) NSString* comment3;
@property(nonatomic, retain) NSString* comment4;
@property(nonatomic, retain) NSDate* date;
@property(nonatomic, retain) NSDate* dateAdded;
@property(nonatomic, retain) NSDate* dateOpened;
@property(nonatomic, retain) NSNumber* displayStyle;
@property(nonatomic, retain) NSNumber* id;
@property(nonatomic, retain) NSString* modality;
@property(nonatomic, retain) NSNumber* mountedVolume __deprecated;
@property(nonatomic, retain) NSString* name;
@property(nonatomic, retain) NSNumber* numberOfImages;
@property(nonatomic, retain) NSNumber* rawNoFiles;
@property(nonatomic, retain) NSNumber* numberOfKeyImages;
@property(nonatomic, retain) NSNumber* rotationAngle;
@property(nonatomic, retain) NSNumber* scale;
@property(nonatomic, retain) NSNumber* hasROIs;
@property(nonatomic, retain) NSNumber* hasKeyImages;
@property(nonatomic, retain) NSString* seriesDescription;
@property(nonatomic, retain) NSString* seriesDICOMUID;
@property(nonatomic, retain) NSString* seriesInstanceUID;
@property(nonatomic, retain) NSString* seriesSOPClassUID;
@property(nonatomic, retain) NSNumber* stateText;
@property(nonatomic, retain) NSData* thumbnail;
@property(nonatomic, retain) NSNumber* windowLevel;
@property(nonatomic, retain) NSNumber* windowWidth;
@property(nonatomic, retain) NSNumber* xFlipped;
@property(nonatomic, retain) NSNumber* xOffset;
@property(nonatomic, retain) NSNumber* yFlipped;
@property(nonatomic, retain) NSNumber* yOffset;
@property(nonatomic, retain) NSData *dictionaryData;
@property(nonatomic, retain) NSOrderedSet* images;
@property(nonatomic, retain) DicomStudy* study;
@property(nonatomic, retain) NSString* bodyPart;
@property int latestDistantNumberOfImages;
@property(nonatomic, retain) NSDate* firstImageDate;
@property(nonatomic, retain) NSDate* lastImageDate;
@property(nonatomic, retain) NSNumber* hiddenWebPortal;

@property(nonatomic, retain) NSNumber* dateTimeZone, *dateAddedTimeZone, *dateOpenedTimeZone;

- (int) multiframesNumber;
- (BOOL) computeHasROIs;
- (NSOrderedSet *)paths;
- (NSSet*) keyImages;
- (float) viewedPercentage;
- (BOOL) hasPixels;
- (NSArray*) sortedKeyImages;
- (NSArray*) sortedImages;
- (DicomImage*) middleImage;
- (NSInteger) firstKeyOrROIImage;
- (NSInteger) lastKeyOrROIImage;
- (NSInteger) nextKeyOrROIImageTo: (NSInteger) index;
- (NSInteger) nextKeyOrROIImageTo: (NSInteger) index forward: (BOOL) forward;
- (NSComparisonResult) compareName:(DicomSeries*)series;
- (NSNumber*) rawNoFiles;
- (DicomSeries*) previousSeries;
- (DicomSeries*) nextSeries;
- (NSArray*) sortDescriptorsForImages;
+ (NSArray*) sortDescriptorsForImages;
- (NSString*) uniqueFilename;
- (BOOL) isDistant;
- (NSTimeInterval) acquisitionDuration;
- (void) computeDuration;
+ (void) recomputeLocalizersSeriesInstanceUIDForStudies: (NSSet*) studiesSet;
+ (void) recomputeSeriesUIDForSeries: (DicomSeries*) series;
- (NSString*) type;
- (NSImage*) thumbnailImage;
- (NSString*) ROIsDescription;
- (void) addBodyPart: (NSString*) bp;
- (NSArray*) imagesWithROIs;
- (NSArray*) imagesWithROIsDisplayedInKeyImagesWindow: (BOOL) imagesWithROIsDisplayedInKeyImagesWindow;
- (BOOL) areThereImagesWithROIsDisplayedInKeyImagesWindow: (BOOL) displayedInKeyImagesWindow;
- (void) purgeCaches;
- (NSArray*) imagesAsScreenCapture;
- (NSArray*) imagesAsScreenCapture:(NSRect)frame;
- (NSArray*) imagesAsScreenCapture:(NSRect)frame dicomImages:(NSArray*) dcmImages;
- (NSArray*) imagesAsScreenCapture:(NSRect)frame dicomImages:(NSArray*) dcmImages annotationsLevel: (annotationsLevel) annotationsLevel;
-(NSArray*) imagesAsScreenCapture:(NSRect)frame dicomImages:(NSArray*) dcmImages annotationsLevel: (annotationsLevel) annotationsLevel cinteRate: (NSInteger*) cineRate;
+ (NSRect) frameForImageAsScreenCapture;
- (NSArray*) presentationStates;
- (NSArray*) applyPresentationState;
- (NSString*) callingAET;
- (NSString*) calledAET;
- (NSString *) hostname;
- (NSDictionary*) dictionary;
- (long) getNewAndUniqueSeriesIDAfterCurrentSeriesID;
- (void) setDictionary: (NSDictionary*) dict;
- (void) addToDictionaryObject: (id) object forKey: (NSString*) key;
- (void) removeKeyFromDictionaryObject:(NSString*) key;
+ (void) initCaptureScreenWindow;
- (SliceOrientation) orientation;
- (BOOL) isVolumic;
@end

@interface DicomSeries (CoreDataGeneratedAccessors)
- (void) addImagesObject:(DicomImage *)value;
- (void) removeImagesObject:(DicomImage *)value;
- (void) addImages:(NSSet *)value;
- (void) removeImages:(NSSet *)value;
@end
