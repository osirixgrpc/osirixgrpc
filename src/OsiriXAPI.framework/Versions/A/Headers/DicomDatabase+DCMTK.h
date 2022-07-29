/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "DicomDatabase.h"
#import "AppController.h"

@interface DicomDatabase (DCMTK)

+(BOOL)fileNeedsDecompression:(NSString*)path;
+(BOOL)compressDicomFilesAtPaths:(NSArray*)paths;
+(BOOL)compressDicomFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
+(BOOL)decompressDicomFilesAtPaths:(NSArray*)paths;
+(BOOL)decompressDicomFilesAtPaths:(NSArray*)paths intoDirAtPath:(NSString*)destDir;
+(NSString*)extractReportSR:(NSString*)dicomSR contentDate:(NSDate*)date;
+(BOOL)testFiles:(NSArray*)files;

@end
