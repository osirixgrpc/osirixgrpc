/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#ifdef __cplusplus
#include "dsrdoc.h"
#else
typedef char DSRDocument;
#endif

#import <Cocoa/Cocoa.h>


#import "ROI.h"
#import "DicomImage.h"

@interface SRAnnotation : NSObject
{
	DSRDocument			*document;
	DicomImage          *image;
	BOOL				_newSR;
	NSString			*_seriesInstanceUID, *_DICOMSRDescription, *_DICOMSeriesNumber, *_reportURL;
	NSData				*_dataEncapsulated;
	NSDate				*_contentDate;
}

/** Extracts ROI as NSData from a DICOM SR
 * @param path File path
 */
+ (NSData *) roiFromDICOM:(NSString *)path;
+ (BOOL) hasRoiFromDICOM:(NSString *)path;

/** Creates a DICOM SR from an array of ROIs
 * @param rois Array of ROI to archive
 * @param path Path to file 
 * @param image the image related to the ROI array
 */
+ (NSString*) archiveROIsAsDICOM:(NSArray *)rois toPath:(NSString *)path  forImage:(DicomImage*)image;


+ (NSString*) getImageRefSOPInstanceUID:(NSString*) path;
+ (NSString*) getReportFilenameFromSR:(NSString*) path;

- (id) initWithROIs:(NSArray *)ROIs  path:(NSString *)path forImage:(NSManagedObject*) im;
- (id) initWithContentsOfFile:(NSString *)path;
- (id) initWithDictionary:(NSDictionary *) dict path:(NSString *) path forImage: (DicomImage*) im;
- (id) initWithWindowsState:(NSData *) dict path:(NSString *) path forImage: (DicomImage*) im;
- (id) initWithFileReport:(NSString *) file path:(NSString *) path forImage: (DicomImage*) im contentDate: (NSDate*) d;
- (id) initWithData:(NSData *) dict path:(NSString *) path forImage: (DicomImage*) im seriesNumber: (int) number seriesDescription: (NSString*) description;
- (id) initWithURLReport:(NSString *) s path:(NSString *) path forImage: (DicomImage*) im;
- (void) addROIs:(NSArray *)someROIs;
- (NSArray *) ROIs;
- (BOOL) writeToFileAtPath:(NSString *)path;
- (NSString *) seriesInstanceUID;
- (void) setSeriesInstanceUID: (NSString *)seriesInstanceUID;
- (NSString *) sopInstanceUID;
- (NSString *) sopClassUID;
- (NSString *) seriesDescription;
- (NSString *) seriesNumber;
- (NSData*) dataEncapsulated;
- (NSString*) reportURL;
- (NSDictionary*) annotations;
@end
