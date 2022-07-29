/*=========================================================================
 Program:   OsiriX
 
 Copyright (c) Pixmeo SARL
 All rights reserved.
  =========================================================================*/

#import <Foundation/Foundation.h>

#ifdef __cplusplus
class DcmDataset;
class DcmMetaInfo;
#else
#ifndef DCMDATASETDEFINED
#define DCMDATASETDEFINED
typedef char* DcmDataset;
#endif
typedef char* DcmMetaInfo;
#endif

@interface DicomBridge : NSObject
{
    NSString *originalFilePath; // if available
    NSDictionary *dictionary;
    NSArray *encodingArray;
    NSStringEncoding encodings[ 10];
    
    BOOL exportKeyword; // XML or JSON
    BOOL exportPixelData; // XML or JSON, replace it with a BulkDataURI
    BOOL useFileURI; // FileURI or http WADO-RS URI ?
    
    // file:/home/gunter/testdata/IMAGES/JPLY/MR1_JPLY?offset=1864&length=65536
    // http://{SERVICE}/studies/{StudyInstanceUID}/series/{SeriesInstanceUID}/instances/{SOPInstanceUID}/bulkdata/x7fe00010
}

@property (retain) NSDictionary *dictionary;
@property (retain, nonatomic) NSArray *encodingArray;
@property (retain) NSString *originalFilePath;
@property BOOL exportKeyword;

// utilties
+ (BOOL) isHexadecimal: (NSString*) string;
+ (BOOL) getGroup: (int*) group andElement: (int*) element fromString: (NSString*) key;
+ (int) dcmtkTransferSyntaxForString: (NSString*) ts;
+ (NSString*) stringForDcmtkTransferSyntax: (int) xfer;

+ (NSString*) jsonFromArray: (NSArray*) array;
+ (NSString*) xmlFromArray: (NSArray*) array;

+ (NSString*) xmlFromDataset: (DcmDataset*) dataset;
+ (NSString*) jsonFromDataset: (DcmDataset*) dataset;

// instances array
+ (NSArray*) bridgesArrayWithXML: (NSString*) xmlStream;
+ (NSArray*) bridgesArrayWithJSON: (NSString*) jsonStream;

// instances
+ (DicomBridge*) bridgeWithJSON: (NSString*) data;
+ (DicomBridge*) bridgeWithJSONData: (NSData*) data;
+ (DicomBridge*) bridgeWithXML: (NSString*) data;
+ (DicomBridge*) bridgeWithXMLData: (NSData*) data;

+ (DicomBridge*) bridgeWithDictionary: (NSDictionary*) dict;

+ (DicomBridge*) bridgeWithDICOMFile: (NSString*) filePath withPixelData: (BOOL) withPixelData;
+ (DicomBridge*) bridgeWithDcmDataset: (DcmDataset*) dataset withPixelData: (BOOL) withPixelData;

// output
- (NSString*) xml;
- (NSString*) json;
- (NSDictionary*) resolvedDictionary;

- (BOOL) saveAsDICOMToFile: (NSString*) file;

- (DcmMetaInfo*) dcmMetaInfo;
- (DcmMetaInfo*) dcmMetaInfo: (DcmMetaInfo *) dataset;
- (DcmDataset*) dcmDataset;
- (DcmDataset*) dcmDataset: (DcmDataset *) dataset;
@end
