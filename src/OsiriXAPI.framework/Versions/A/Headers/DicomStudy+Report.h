/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DicomStudy.h"

@interface DicomStudy (Report)

// report to pdf
+(void)transformReportAtPath:(NSString*)reportPath toPdfAtPath:(NSString*)outPdfPath;
-(void)saveReportAsPdfAtPath:(NSString*)path;
-(NSString*)saveReportAsPdfInTmp;

// pdf to dicom
+(void)transformPdfAtPath:(NSString*)pdfPath toDicomAtPath:(NSString*)outDicomPath usingSourceDicomAtPath:(NSString*)sourcePath;
+(void)transformPdfAtPath:(NSString*)pdfPath toDicomAtPath:(NSString*)outDicomPath usingSourceDicomAtPath:(NSString*)sourcePath seriesDescription:(NSString*) seriesDescription;
-(void)transformPdfAtPath:(NSString*)pdfPath toDicomAtPath:(NSString*)outDicomPath;

+(void)transformSTLAtPath:(NSString*)stlPath toDicomAtPath:(NSString*)outDicomPath usingSourceDicomAtPath:(NSString*)sourcePath seriesDescription:(NSString*) seriesDescription;

-(BOOL) transformPath:(NSString*) inPath toDicomAtPath:(NSString*) outPath seriesDescription:(NSString*) seriesDescription;
-(BOOL) transformPath:(NSString*) inPath seriesDescription:(NSString*) seriesDescription;

-(void)saveReportAsDicomAtPath:(NSString*)path;
-(NSString*)saveReportAsDicomInTmp;
- (void) deleteReport;
-(BOOL) addToReportROIs:(BOOL) rois andKeyImages:(BOOL) keys;
- (BOOL) addToReportCurrentImage;
+(NSString*) imageBlockForDicomImage: (DicomImage*) image;
+(NSString*) imageBlockForImage: (NSImage*) im withDicomImage: (DicomImage*) image;
+(NSArray*) acceptedExtensions;
-(NSString*) HTMLReport;
@end
