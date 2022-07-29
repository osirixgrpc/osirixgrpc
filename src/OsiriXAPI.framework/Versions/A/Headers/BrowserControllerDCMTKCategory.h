/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "BrowserController.h"

/** \brief  Category for DCMTK calls from BrowserController */

@interface BrowserController (BrowserControllerDCMTKCategory)
+ (NSString*) compressionString: (NSString*) string;

#ifndef OSIRIX_LIGHT
- (NSData*) getDICOMFile:(NSString*) file inSyntax:(NSString*) syntax quality: (int) quality;
- (BOOL) testFiles: (NSArray*) files __deprecated;
- (BOOL) needToCompressFile: (NSString*) path __deprecated;
- (BOOL) compressDICOMWithJPEG:(NSArray *) paths __deprecated;
- (BOOL) compressDICOMWithJPEG:(NSArray *) paths to:(NSString*) dest __deprecated;
- (BOOL) decompressDICOMList:(NSArray *) files to:(NSString*) dest __deprecated;
- (NSData*) getPixelData:(NSString*) file;
#endif
@end
