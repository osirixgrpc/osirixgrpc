/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import <OsiriX/DCMFramework.h>

#undef verify
#include "dcdatset.h"
#include "ofcond.h"
#include "dcmqrdbi.h"

//NSString * const OsiriXFileReceivedNotification;

/** \brief  Finds the appropriate study/series/image for Q/R
*
* Finds the appropriate study/series/image for Q/R
* Interface between server and database 
*/

@class DicomDatabase, WebPortalUser;

@interface OsiriXSCPDataHandler : NSObject
{
	NSArray *findArray;
	NSString *specificCharacterSet;
	NSEnumerator *findEnumerator;
    int findEnumeratorIndex;
	NSString *callingAET;
    
	int numberMoving;
	
	NSStringEncoding encoding;
	int moveArrayEnumerator;
    NSArray *moveArray;
	NSMutableDictionary *logDictionary;
	NSMutableDictionary *findTemplate;
    
    int prepareMoveForDataSetLevel;
}

@property(retain) NSString *callingAET;
@property(readonly) NSArray *findArray;
@property(readonly) NSEnumerator *findEnumerator;
@property(retain, nonatomic) NSString *specificCharacterSet;

+ (id)allocRequestDataHandler;
+ (NSArray*) databases;

-(NSTimeInterval)endOfDay:(NSCalendarDate *)day;
-(NSTimeInterval)startOfDay:(NSCalendarDate *)day;

- (NSPredicate *)predicateForDataset:( DcmDataset *)dataset compressedSOPInstancePredicate: (NSPredicate**) csopPredicate seriesLevelPredicate: (NSPredicate**) SLPredicate;
- (void)studyDatasetForFetchedObject:(id)fetchedObject dataset:(DcmDataset *)dataset;
- (void)seriesDatasetForFetchedObject:(id)fetchedObject dataset:(DcmDataset *)dataset;
- (void)imageDatasetForFetchedObject:(id)fetchedObject dataset:(DcmDataset *)dataset;

- (OFCondition)prepareFindForDataSet:( DcmDataset *)dataset;
- (OFCondition)prepareFindForDataSet: (DcmDataset *) dataset forUser:(WebPortalUser*) user;
- (OFCondition)prepareMoveForDataSet:( DcmDataset *)dataset;

- (BOOL)findMatchFound;
- (int)moveMatchFound;

- (OFCondition)nextFindObject:(DcmDataset *)dataset  isComplete:(BOOL *)isComplete;
- (OFCondition)nextMoveObject:(char *)imageFileName;

+ (DB_LEVEL) queryLevelForString: (const char*) level;
@end
