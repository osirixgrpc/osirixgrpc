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

NSString* sopInstanceUIDDecode( unsigned char *r, int length);
void* sopInstanceUIDEncode( NSString *sopuid);

#define OsirixDicomImageSizeUnknown INT_MAX

@class DCMSequenceAttribute, DicomSeries, DICOMExport, DicomDatabase;

@interface NSData (OsiriX)
- (BOOL) isEqualToSopInstanceUID:(NSData*) sopInstanceUID;
@end

/** \brief  Core Data Entity for an image (frame) */

@interface DicomImage : NSManagedObject
{
	NSString	*completePathCache;
	
	NSString	*sopInstanceUID;
    long long   sopInstanceUIDNumber;
	NSNumber	*inDatabaseFolder;
	NSNumber	*height, *width;
	NSNumber	*numberOfFrames;
	NSNumber	*numberOfSeries;
	NSNumber	*isKeyImage, *dicomTime;
	NSString	*extension;
	NSString	*modality;
	NSString	*fileType;
    NSString    *cachedSRPath;
    NSString    *cachedSeriesInstanceUID;
    
    NSImage     *_thumbnail;
    
    NSArray     *rois; // temporary && cache : used in [DicomSeries imagesWithROIsDisplayedInKeyImagesWindow];
    
    id sortingValue;
}

@property(retain) NSArray *rois;
@property(retain) NSNumber* numberOfFrames;
@property(retain) id sortingValue;

@property(nonatomic, retain) NSString* comment;
@property(nonatomic, retain) NSString* comment2;
@property(nonatomic, retain) NSString* comment3;
@property(nonatomic, retain) NSString* comment4;
@property(nonatomic, retain) NSData* compressedSopInstanceUID;
@property(nonatomic, retain) NSDate* date;
@property(nonatomic, retain) NSNumber* frameID;
@property(nonatomic, retain) NSNumber* instanceNumber;
@property(nonatomic, retain) NSNumber* importedFile;
@property(nonatomic, retain) NSNumber* pathNumber;
@property(nonatomic, retain) NSString* pathString;
@property(nonatomic, retain) NSNumber* rotationAngle;
@property(nonatomic, retain) NSNumber* scale;
@property(nonatomic, retain) NSNumber* sliceLocation;
@property(nonatomic, retain) NSString* stateText;
@property(nonatomic, retain) NSString* storedExtension;
@property(nonatomic, retain) NSString* storedFileType;
@property(nonatomic, retain) NSNumber* storedHeight;
@property(nonatomic, retain) NSNumber* storedInDatabaseFolder;
@property(nonatomic, retain) NSNumber* storedIsKeyImage;
@property(nonatomic, retain) NSString* storedModality;
@property(nonatomic, retain) NSNumber* storedMountedVolume __deprecated;
@property(nonatomic, retain) NSNumber* storedNumberOfFrames;
@property(nonatomic, retain) NSNumber* storedNumberOfSeries;
@property(nonatomic, retain) NSNumber* storedWidth;
@property(nonatomic, retain) NSNumber* windowLevel;
@property(nonatomic, retain) NSNumber* windowWidth;
@property(nonatomic, retain) NSNumber* generatedByOsiriX;
@property(nonatomic, retain) NSNumber* xFlipped;
@property(nonatomic, retain) NSNumber* xOffset;
@property(nonatomic, retain) NSNumber* yFlipped;
@property(nonatomic, retain) NSNumber* yOffset;
@property(nonatomic, retain) NSNumber* zoom;
@property(nonatomic, retain) DicomSeries* series;
@property(nonatomic, retain) NSNumber *cloudDownloaded, *cloudUploaded;
@property(nonatomic, retain) NSNumber *viewedImage;

+ (void) initCaptureScreenWindow;
+ (NSArray*) uniquePathsForDicomImageArray: (NSArray*) images;
- (NSNumber*) isImageStorage;
- (NSNumber*) isPDFStorage;
- (BOOL) isPDFRenderableDocument;
+ (NSData*) sopInstanceUIDEncodeString:(NSString*) s;
- (NSString*) uniqueFilename;
- (NSString*) seriesInstanceUID;
- (NSNumber*) numberOfSeries;
- (void) setNumberOfSeries:(NSNumber*) f;
- (NSSet*) paths;
- (NSString*) completePath;
- (NSString*) completePathResolved;
#ifndef OSIRIX_LIGHT
- (DCMSequenceAttribute*) graphicAnnotationSequence;
#endif
- (NSString*) type;
- (NSImage*) image;
- (NSImage*) thumbnail;
- (NSNumber*) inDatabaseFolder;
- (void) setInDatabaseFolder:(NSNumber*) f;
- (NSString*) path;
- (void) setPath:(NSString*) p;
- (NSImage*) imageAsScreenCapture:(NSRect)frame annotationsLevel: (annotationsLevel) annotationsLevel useROIWLWW: (BOOL) useROIWLWW;
- (NSImage*) imageAsScreenCapture:(NSRect)frame annotationsLevel: (annotationsLevel) annotationsLevel;
- (NSImage*) imageAsScreenCapture:(NSRect)frame;
- (NSImage*) imageAsScreenCapture;
- (NSDictionary*) imageAsDICOMScreenCapture:(DICOMExport*) exporter;
- (NSDictionary*) imageAsDICOMScreenCapture:(DICOMExport*) exporter exporterForRGB: (DICOMExport*) exporterRGB;
- (NSArray*) ROIsDescription;
- (NSArray*) ROIs;
- (NSImage*) thumbnailIfAlreadyAvailable;
- (void) setThumbnail:(NSImage*)image;
- (NSString*) completePathWithDownload:(BOOL) download supportNonLocalDatabase: (BOOL) supportNonLocalDatabase;
- (NSString*) completePathForLocalPath:(NSString*) path;
- (NSString*) SRFilenameForFrame: (int) frameNo;
- (NSString*) SRPathForFrame: (int) frameNo;
- (NSString*) SRPath;
- (NSString*) sopInstanceUID;
- (void) setSopInstanceUID: (NSString*) s;
@property(nonatomic, retain) NSString* modality;

- (NSString*) extension;
- (void) setExtension:(NSString*) f;
- (NSNumber*) height;
- (NSNumber*) width;
- (void) setHeight:(NSNumber*) f;
- (void) setWidth:(NSNumber*) f;
- (NSString*) fileType;
- (void) setFileType:(NSString*) f;
- (NSNumber*) isKeyImage;
- (void) setIsKeyImage:(NSNumber*) f;
- (void) setIsKeyImage:(NSNumber*) f archiveAnnotationsAsDICOMSR: (BOOL) archiveAnnotationsAsDICOMSR;

+ (NSMutableArray*) dicomImagesInObjects:(NSArray*)objects;

@end

