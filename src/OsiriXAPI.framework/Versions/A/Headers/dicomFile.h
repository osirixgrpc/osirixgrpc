/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#define MINIMUM_TARGET_SIZE_FOR_PDF 1200
#define ItIsADICOMDIR -8237

/** \brief  Parses files for importing into the database */

@interface DicomFile: NSObject
{
    NSString            *name;
    NSString            *study;
    NSString            *serie;
    NSString            *filePath, *fileType;
    NSString            *Modality;
	NSString			*SOPUID;
	NSString			*imageType;
    
    NSString            *studyID;
    NSString            *serieID;
    NSString            *imageID;
	NSString			*patientID;
	NSString			*studyIDs;
	NSString			*seriesNo;
    NSDate              *date;
	
	long				width, height;
	long				NoOfFrames;
	long				NoOfSeries;
    
	NSMutableDictionary *dicomElements;
}

@property(retain) NSString *serieID, *serie, *studyID;
@property(retain, nonatomic) NSString *filePath;

+ (NSArray*) zipExtensions;
+ (NSArray*) moviesExtensions;

// file functions
+ (BOOL) isTiffFile:(NSString *) file; /**< Test for TIFF file format */
+ (BOOL) isFVTiffFile:(NSString *) file; /**< Test for FV TIFF file format */
+ (BOOL) isDICOMFile:(NSString *) file; /**< Test for DICOM file format */
+ (BOOL) isDICOMFile:(NSString *) file compressed:(BOOL*) compressed; /**< Test for DICOM file format, returns YES for compressed BOOL if Transfer syntax is compressed. */
+ (BOOL) isDICOMFile:(NSString *) file compressed:(BOOL*) compressed image:(BOOL*) image;
+ (BOOL) isDICOMFile:(NSString *) file compressed:(BOOL*) compressed image:(BOOL*) image SOP:(NSString**) SOP;
+ (BOOL) isDICOMFile:(NSString *) file compressed:(BOOL*) compressed transferSyntax:(int*) ts image:(BOOL*) image SOP:(NSString**) SOP;
+ (BOOL) isXMLDescriptedFile:(NSString *) file; /**< Test for XML descripted  file format */
+ (BOOL) isXMLDescriptorFile:(NSString *) file; /**< Test for XML descriptor file format. Fake DICOM for other files with XML descriptor*/
+ (void) setFilesAreFromCDMedia: (BOOL) f; /**< Set flag for filesAreFromCDMedia */
+ (void) setDefaults;  /**< Set DEFAULTSSET flag to NO */
+ (void) resetDefaults; /**< Resets to user defaults */
/**  Return string with invalid characters replaced
* replaces @"^" with @" "
* replaces @"/" with @"-"
* replaces @"\r" with @""
* replaces @"\n" with @""
* @":" withString:@"-"
* removes empty space at end of strings
*/
+ (NSString*) NSreplaceBadCharacter: (NSString*) str; 
+ (char *) replaceBadCharacter:(char *) str encoding:(NSStringEncoding) encoding; /**< Same as NSreplaceBadCharacter, but using char* and encodings */
+ (NSString *) stringWithBytes:(char *) str encodings:(NSStringEncoding*) encoding; /**< Convert char* str with NSStringEncoding* encoding to NSString */
+ (NSString *) stringWithBytes:(char *) str encodings:(NSStringEncoding*) encoding trim:(BOOL) trim;
+ (NSString *) stringWithBytes:(char *) str encodings:(NSStringEncoding*) encoding replaceBadCharacters:(BOOL) replace; /**< Convert char* str with NSStringEncoding* encoding to NSString */
+ (NSString *) stringWithBytes:(char *) str encodings:(NSStringEncoding*) encodings replaceBadCharacters:(BOOL) replace trim:(BOOL) trim;
- (NSPDFImageRep*) PDFImageRep; /**< Get a PDFImageRep from DICOM SR file */
- (NSString*) PDFFile;
- (long) NoOfFrames; /**< Number of frames in the file */
- (long) getWidth; /**<  Returns image width */
- (long) getHeight; /**< Return image Height */
- (long) NoOfSeries; /**< Returns number of seris in the file */
+ (id) dicomFileWithPath:(NSString*) f; /**< Init with file at location NSString* f */
- (id) init:(NSString*) f; /**< Init with file at location NSString* f */
- (id) init:(NSString*) f DICOMOnly:(BOOL) DICOMOnly; /**< init with file at location NSString* f DICOM files only if DICOMOnly = YES */
- (id) initRandom; /**< Inits and returns an empty dicomFile */
//- (id) initWithXMLDescriptor: (NSString*)pathToXMLDescriptor path:(NSString*) f; /**< Init with XMLDescriptor for information and f for image data */
- (NSString*) patientUID; /**< Returns the patientUID */
+ (NSString*) patientUID: (NSDictionary*) src; /**< Returns the patientUID */
+ (NSString*) patientUIDwithName: (NSString*) name birthdate: (NSDate*) birthdate patientID: (NSString*) patID; /**< Returns the patientUID */
- (void) compressed:(BOOL*) compressed image:(BOOL*) image SOP:(NSString**) SOP;

/** Returns a dictionary of the elements used to import into the database
* Keys:
* @"studyComment", @"studyID", @"studyDescription", @"studyDate", @"modality", @"patientID", @"patientName",
* @"patientUID", @"fileType", @"comments", @"album", @"SOPClassUID", @"SOPUID", @"institutionName",
* @"referringPhysicianName", @"performingPhysicianName", @"accessionNumber", @"patientAge", @"patientBirthDate",
* @"patientSex", @"cardiacTime", @"protocolName", @"sliceLocation", @"imageID", @"seriesNumber", @"seriesDICOMUID",
* @"studyNumber", @"seriesID", @"hasDICOM"
* */

- (NSMutableDictionary *)dicomElements;  
- (id)elementForKey:(id)key;  /**< Returns the dicomElement for the key */
- (short)getPluginFile;  /**< Looks for a plugin to decode the file. If one is found decodes the file */
/** Parses the fileName to get the Series/Study/Image numbers
*  Used for files that don't have the information embedded such as TIFFs and jpegs
*  In these cases the files are sorted based on the file name.
*  Numbers at the end become the image number. The remainder of the file becomes the Series and Study ID 
*/
- (void)extractSeriesStudyImageNumbersFromFileName:(NSString *)tempString;  

-(short) getDicomFile;  /**< Decode DICOM.  Returns -1 for failure 0 for success */

#ifndef DECOMPRESS_APP
-(short) getNIfTI; /**< Decode NIfTI  Returns -1 for failure 0 for success */
+(NSXMLDocument *) getNIfTIXML : (NSString *) file; /**< Converts NIfTI to XML */
+ (BOOL) isNIfTIFile:(NSString *) file; /**< Test for Nifti file format */
#endif

/** Returns the COMMENTSAUTOFILL default. 
* If Yes, comments will be filled from the DICOM tag  commentsGroup/commentsElement
*/
- (BOOL) commentsFromDICOMFiles;
- (BOOL) autoFillComments; 
- (BOOL) splitMultiEchoMR; /**< Returns the splitMultiEchoMR default If YES, splits multi echo series into separate series by Echo number. */
- (BOOL) useSeriesDescription; /**< Returns the useSeriesDescription default. */
- (BOOL) noLocalizer; /**< Returns the NOLOCALIZER default. */
- (NSDictionary*) combineSeries;
- (NSDictionary*) splitSeries;
- (BOOL) oneFileOnSeriesForUS; /**< Returns the oneFileOnSeriesForUS default */
//- (BOOL) checkForLAVIM; /**< Returns the CHECKFORLAVIM default. */
- (BOOL) separateCardiac4D; /**< Returns the SEPARATECARDIAC4D default. If YES separates cardiac studies into separate gated series. */
- (BOOL) containsString: (NSString*) s inArray: (NSArray*) a;
+ (BOOL) containsLocalizerInString: (NSString*) str;
+ (NSString*) seriesInstanceUIDForFile: (NSString*) file;
+ (NSArray*) combineSplitModalities;
+ (NSDictionary*)combineSeriesDictionary;
+ (NSDictionary*)splitSeriesDictionary;
@end


