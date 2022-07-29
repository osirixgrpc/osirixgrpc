/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

typedef enum {
    unknownFilesOnDistantServer = 0,
    checkingOnDistantServer = 1,
    noFilesOnDistantServer = 2,
    partiallyAvailableOnDistantServer = 3,
    allFilesOnDistantServer = 4
} SyncDistantServerState;

@class DicomSeries, DicomImage;

/** \brief  Core Data Entity for a Study */
@interface DicomStudy : NSManagedObject
{
	BOOL isHidden;
	NSNumber *dicomTime, *cachedRawNoFiles;
    NSTimeInterval cachedRawNoFilesTime;
    NSUInteger _numberOfImagesWhenCachedModalities;
	NSString *cachedModalites, *cacheYearOldAcquisition, *cacheYearOld;
    NSColor *cachedColor;
    NSArray *cachedPresentationStates;
    NSArray *cacheROIs;
    DicomSeries *cachedROISRSeries;
    NSSet *cacheKeyImages;
    BOOL reentry;
    
    BOOL cachedIsIncompleteStudy;
    NSTimeInterval cachedIsIncompleteStudyDate;
    
    int numberOfSeries;
    
    NSDictionary *distantServer;
    NSArray *distantSOPInstances;
    
    int avoidReentry3;
}
@property (nonatomic) int32_t distantServerState;
@property (nonatomic) double distantServerStateTime;
@property(nonatomic, retain) NSString* accessionNumber;
@property(nonatomic, retain) NSString* requestedProcedureID;
@property(nonatomic, retain) NSString* color;
@property(nonatomic, retain) NSString* studyState;
@property(nonatomic, retain) NSString* bodyPart;
@property(nonatomic, retain) NSString* comment;
@property(nonatomic, retain) NSString* comment2;
@property(nonatomic, retain) NSString* comment3;
@property(nonatomic, retain) NSString* comment4;
@property(nonatomic, retain) NSDate* date;
@property(nonatomic, retain) NSDate* dateAdded;
@property(nonatomic, retain) NSDate* dateOfBirth;
@property(nonatomic, retain) NSString* dateOfBirthString;
@property(nonatomic, retain) NSDate* dateOpened;
@property(nonatomic, retain) NSString* dictateURL;
@property(nonatomic, retain) NSNumber* expanded;
@property(nonatomic, retain) NSNumber* hasDICOM;
@property(nonatomic, retain) NSNumber* hasKeyImages;
@property(nonatomic, retain) NSNumber* hasROIs;
@property(nonatomic, retain) NSString* id;
@property(nonatomic, retain) NSString* institutionName;
@property(nonatomic, retain) NSString* manufacturerModelName;
@property(nonatomic, retain) NSNumber* lockedStudy;
@property(nonatomic, retain) NSString* modality;
@property(nonatomic, retain) NSString* name;
@property(nonatomic, retain) NSNumber* numberOfImages;
@property(nonatomic, retain) NSString* patientID;
@property(nonatomic, retain) NSString* patientSex;
@property(nonatomic, retain) NSString* patientUID;
@property(nonatomic, retain) NSString* performingPhysician;
@property(nonatomic, retain) NSString* referringPhysician;
@property(nonatomic, retain) NSString* reportURL;
@property(nonatomic, retain) NSNumber* stateText;
@property(nonatomic, retain) NSString* studyInstanceUID;
@property(nonatomic, retain) NSString* studyName;
@property(nonatomic, retain) NSData* windowsState;
@property(nonatomic, retain) NSData *dictionaryData;
@property(nonatomic, retain) NSSet* albums;
@property(nonatomic, retain) NSSet* series;
@property(nonatomic, retain) NSNumber *cloudDownloaded, *cloudUploaded;
@property(nonatomic, retain) NSNumber *cloudUploadFailed;
@property(nonatomic, retain) NSDate* firstImageDate;
@property(nonatomic, retain) NSDate* lastImageDate;
@property(nonatomic, retain) NSString* viewedBy;
@property(nonatomic, retain) NSDate* viewedByDate;
@property(nonatomic, retain) NSArray *distantSOPInstances;
@property(nonatomic, retain) NSDictionary *distantServer;
@property(nonatomic, retain) NSNumber *priority;
@property(nonatomic, retain) NSNumber *hiddenWebPortal;

@property(nonatomic, retain) NSNumber* dateTimeZone, *dateAddedTimeZone, *dateOfBirthTimeZone, *dateOpenedTimeZone;

+ (NSDate*) convertDate:(NSDate*) date withTimeZone:(NSNumber*) savedTimeZone;
+ (NSNumber*) timeZoneForDate:(NSDate*) date;

+ (NSRecursiveLock*) dbModifyLock;
+ (NSString*) formattedPatientName: (NSString*) n;
+ (NSString*) soundex: (NSString*) s;
- (NSString*) soundex;
+ (NSString*) yearOldFromDateOfBirth: (NSDate*) dateOfBirth;
+ (NSString*) yearOldAcquisition:(NSDate*) acquisitionDate FromDateOfBirth: (NSDate*) dateOfBirth;
+ (BOOL) displaySeriesWithSOPClassUID: (NSString*) uid andSeriesDescription: (NSString*) description;
+ (BOOL) displaySeriesWithSOPClassUID: (NSString*) uid andSeriesDescription: (NSString*) description containingOnlyPixels: (BOOL) pixels;
+ (NSArray*) seriesSortDescriptors;
+ (NSArray*) seriesSortDescriptorsWithSubKey: (NSString*) subKey;
+ (NSArray*) seriesSortDescriptorsWithSubKey: (NSString*) subKey addStudyDateSorting: (BOOL) addStudyDateSorting;
+ (void) resetPreferences;
- (NSNumber*) noFiles;
- (NSTimeInterval) acquisitionDuration;
- (NSString*) acquisitionDurationFormatted;
- (void) computeDurationAndSeries: (BOOL) computeSeries;
- (void) computeDuration;
- (NSSet*) paths;
- (NSSet*) keyImages;
- (DicomImage*) imageWithPixels;
- (NSArray*) roiAndKeyImages;
- (NSArray*) roiAndKeyImagesWithOnlyROIsDisplayedInKeyImagesWindow;
- (NSArray*) roiAndKeyImagesWithROIsDisplayedInKeyImagesWindow: (BOOL) displayedInKeyImagesWindow;
- (NSString*) yearOld;
- (NSString*) yearOldAcquisition;
- (NSString*) yearOldNowAndAtAcquisition;
- (NSString*) dateOfBirthFormatted;
- (NSSet*) images;
- (NSNumber*) rawNoFiles;
- (void) resetCachedRawNoFiles;
- (NSString*) modalities;
+ (NSString*) displayedModalitiesForSeries: (NSArray*) seriesModalities;
+ (NSArray*) chronologicalColors;
- (NSNumber*) chronologicalNumber;
- (NSColor*) chronologicalColor;
- (NSArray*) imageSeries;
- (NSArray*) imageSeriesContainingPixels:(BOOL) pixels;
- (NSArray*) imageSeriesContainingPixels:(BOOL) pixels includeLocalizersSeries: (BOOL) includeLocalizersSeries;
- (NSArray*) imageSeriesContainingPixels:(BOOL) pixels includeLocalizersSeries: (BOOL) includeLocalizersSeries sorted:(BOOL) sorted;
- (NSArray*) keyObjectSeries;
- (NSArray*) keyObjects;
- (NSArray*) presentationStateSeries;
- (NSArray*) presentationStateObjects;
- (NSArray*) presentationStateDictionaries;
- (NSArray*) waveFormSeries;
- (NSString*) roiPathForImage: (DicomImage*) image inArray: (NSArray*) roisArray commentsArray: (NSArray*) commentsArray;
- (NSString*) roiPathForImage: (DicomImage*) image inArray: (NSArray*) roisArray;
- (NSString*) roiPathForImage: (DicomImage*) image;
- (DicomImage*) roiForImage: (DicomImage*) image inArray: (NSArray*) roisArray commentsArray: (NSArray*) commentsArray;
- (DicomImage*) roiForImage: (DicomImage*) image inArray: (NSArray*) roisArray;
- (NSArray*) OsiriXSRSeries;
- (DicomSeries*) roiSRSeries;
- (DicomSeries*) localizersSeries;
- (DicomSeries*) reportSRSeries;
- (DicomImage*) windowsStateImage;
- (DicomSeries*) windowsStateSRSeries;
- (DicomImage*) reportImage;
- (DicomImage*) annotationsSRImage;
- (DicomImage *) SRImageWithSeriesID: (int) seriesID seriesDescription: (NSString*) seriesDescription;
- (void) recordViewedBy;
- (void) recordViewedBy:(NSString*) username;
- (NSString*) viewedByDateFormatted;
+ (NSString*) getUsername;
- (void) archiveReportAsDICOMSR;
+ (void) setArchiveAnnotationsAsDICOMSR: (BOOL) v;
- (void) archiveAnnotationsAsDICOMSR;
- (void) archiveWindowsStateAsDICOMSR;
- (NSArray*) allWindowsStateSRSeries;
- (void) addBodyPart: (NSString*) bp;
- (BOOL) isHidden;
- (BOOL) isDistant;
- (NSNumber*) dicomTime;
- (void) setHidden: (BOOL) h;
- (NSDictionary*) annotationsAsDictionary;
- (void) applyAnnotationsFromDictionary: (NSDictionary*) rootDict;
- (void) reapplyAnnotationsFromDICOMSR;
- (NSComparisonResult) compareName:(DicomStudy*)study;
- (NSArray*) roiImages;
- (NSArray*) imagesWithROIs;
- (NSArray*) imagesWithROIsDisplayedInKeyImagesWindow: (BOOL) displayedInKeyImagesWindow;
- (BOOL) areThereImagesWithROIsDisplayedInKeyImagesWindow: (BOOL) displayedInKeyImagesWindow;
- (NSArray*) allSeries;
- (NSArray*) generateDICOMSCImagesForKeyImages: (BOOL) keyImages andROIImages: (BOOL) ROIImages;
- (void) setNSColor:(NSColor *)c;
- (NSColor*) NSColor;
- (NSString*) ROIsDescription;
- (NSString*) type;
- (NSString*) calledAET; // Match DCMTKQueryNode
- (NSString*) callingAET; // Match DCMTKQueryNode
- (NSString *)hostname; // Match DCMTKQueryNode
+ (NSArray*) comparativeStudiesForStudy: (id) studySelectedID;
- (NSArray*) studiesForThisPatient;
- (BOOL) computeHasROIs;
- (BOOL) computeHasKeyImages;
- (NSImage*) thumbnailImage;
- (NSData*) thumbnail;
- (NSNumber*) noSeries;
- (void) refresh;
- (void) computeDistantServerState;
- (void) checkDistantServerState;
- (void) checkDistantServerStateUploadIfNoFilesOnDistantServer: (BOOL) uploadIfNoFilesOnDistantServer;
- (void) uploadFilesToCloud:(NSArray*) localExtraDicomImages;
- (void) resetDistanceServerState;
+ (NSString*) scrambleString: (NSString*) t;
- (NSDictionary*) dictionary;
- (void) setDictionary: (NSDictionary*) dict;
- (void) addToDictionaryObject: (id) object forKey: (NSString*) key;
- (void) removeKeyFromDictionaryObject:(NSString*) key;
- (long) getNewAndLastSeriesID;
- (long) getNewAndFirstSeriesID;
- (long) getNewAndUniqueSeriesIDAfterThisSeriesID: (long) startNumber;
+ (BOOL) isSendingStudyID: (NSManagedObjectID*) study;
+ (void) setSendingStudyID: (NSManagedObjectID*) study to:(BOOL) value;
+ (void) setSendingStudyIDs: (NSArray*) studies to:(BOOL) value;
- (BOOL) isExcludedFromWebPortal;
- (void) setExcludedFromWebPortal: (BOOL) add;
@end

@interface DicomStudy (CoreDataGeneratedAccessors)

- (void) addAlbumsObject:(NSManagedObject*) value;
- (void) removeAlbumsObject:(NSManagedObject*) value;
- (void) addAlbums:(NSSet*) value;
- (void) removeAlbums:(NSSet*) value;

- (void) addSeriesObject:(DicomSeries*) value;
- (void) removeSeriesObject:(DicomSeries*) value;
- (void) addSeries:(NSSet*) value;
- (void) removeSeries:(NSSet*) value;

@end

