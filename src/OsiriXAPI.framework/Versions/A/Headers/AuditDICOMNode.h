/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <AppKit/AppKit.h>
#import "CHCSVParser.h"

@class QueryFilter;
@class DicomStudy;
@class DICOMFieldMenu;
@class DicomDatabase;
@class Audit;
@class AuditDatabase;

@interface AuditDICOMNode : NSWindowController <CHCSVParserDelegate>
{
    NSMutableDictionary *currentRow;
    NSMutableArray *csvHeader;
    AuditDatabase *dbParser;
    Audit *importAudit;
    NSMutableSet *importedDates;
    unsigned int totalImported;
}
@property (retain) NSMutableDictionary *currentRow;
@property (retain) NSMutableArray *csvHeader;
@property (retain) AuditDatabase *dbParser;
@property (retain) Audit *importAudit;
@property (retain) NSMutableSet *importedDates;

+ (AuditDICOMNode*) sharedInstance;
- (Audit*) createNewAuditWithName:(NSString*) name sources: (NSArray*) servers;
- (void) getDataFrom: (NSDictionary*) dict;
- (void) getDataFromNodes: (NSArray*) servers fromDate:(NSDate*) fromDate toDate: (NSDate*) toDate auditUID:(NSString*) uid;
- (void) exportAudit: (NSString*) uid toCSV: (NSString*) path;
- (void) importAuditToUID: (NSString*) uid fromCSV: (NSString*) path;
- (void) recomputeSecondaryFieldsForUID:(NSString*) uid;
- (NSString*) jsonTableForParameters:(NSDictionary*) dict;
- (NSArray*) arrayForParameters:(NSDictionary*) dict;
- (NSString*) jsonInfoForParameters:(NSDictionary*) dict;
- (void) anonymizeDatabase:(NSString*) uid;
@end
