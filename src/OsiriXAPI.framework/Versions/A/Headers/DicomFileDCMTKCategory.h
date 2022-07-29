/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "dicomFile.h"

/** \brief  C++ calls for DicomFile 
*
*  Some C++ header from DCMTK and other C++ libs can conflict with Objective C during compilation.
*  Putting them in a separate category prevents compilation errors.
*/

@interface DicomFile (DicomFileDCMTKCategory)

+ (NSArray*) getEncodingArrayForFile: (NSString*) file;
+ (BOOL) isDICOMFileDCMTK:(NSString *) file; /**< Check for validity of DICOM using DCMTK */
+ (BOOL) isNRRDFile:(NSString *) file; /**< Test for NRRD file format */

+ (NSDate*) studyDateFromDataset: (void *) dataset;

+ (NSString*) getDicomField: (NSString*) field forFile: (NSString*) path;
+ (NSString*) getDicomFieldForGroup:(int)gr element:(int)el forFile: (NSString*) path;
+ (NSString*) getDicomFieldForGroup:(int) gr element: (int) el forDcmFileFormat: (void*) ff;

+ (NSData*) getDicomDataForGroup:(int)gr element:(int)el forFile: (NSString*) path;
+ (NSData*) getDicomDataForGroup:(int) gr element: (int) el forDcmFileFormat: (void*) ff;

+ (BOOL) rewriteAsExplicit:(NSString*) path;
+ (BOOL) rewritePath: (NSString*) path asSyntax: (int) syntax;
+ (BOOL) rewritePath: (NSString*) path asSyntax: (int) syntax toPath:(NSString*) savePath;

+ (unsigned short) getVRForElement: (unsigned short) el group: (unsigned short) gr;

- (BOOL) getHologicHeader;
- (short) getDicomFileDCMTK; /**< Decode DICOM using DCMTK.  Returns 0 on success -1 on failure. */
- (short) getNRRDFile; /**< decode NRRD file format.  Returns 0 on success -1 on failure. */
- (NSDictionary*) presentationStateDictionaries;
@end
