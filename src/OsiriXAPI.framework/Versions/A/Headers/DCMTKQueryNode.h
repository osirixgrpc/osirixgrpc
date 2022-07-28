/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "DCMTKServiceClassUser.h"
#import "SendController.h"

#ifndef OSIRIX_LIGHT
@class DCMCalendarDate, DicomDatabase;

#ifdef __cplusplus
class DcmDataset;
#else
#ifndef DCMDATASETDEFINED
#define DCMDATASETDEFINED
typedef char* DcmDataset;
#endif
#endif

/** \brief Base class for query nodes */
@interface DCMTKQueryNode : DCMTKServiceClassUser <NSCopying, NSURLSessionDelegate>
{
	NSMutableArray *_children;
    BOOL _sortChildren;
    NSString *childrenSynchronized;
    
	NSString *_uid;
	NSString *_theDescription;
	NSString *_name, *_rawName;
	NSString *_patientID;
	NSString *_referringPhysician;
    NSString *_performingPhysician;
	NSString *_institutionName;
	NSString *_comments;
    NSString *_interpretationStatusID;
    NSString *_scheduledProcedureStepStatus;
	NSString *_accessionNumber;
    NSString *_bodyPartExamined;
    NSString *_manufacturerModelName;
    NSString *_patientSex;
	DCMCalendarDate *_date;
	DCMCalendarDate *_birthdate;
    NSString *_birthdateString;
	DCMCalendarDate *_time;
	NSString *_modality;
	NSNumber *_numberImages;
	NSString *_specificCharacterSet;
    NSString *_abstractSyntax;
	BOOL showErrorMessage, firstWadoErrorDisplayed, _dontCatchExceptions, _isAutoRetrieve, _noSmartMode;
	OFCondition globalCondition;
    NSUInteger _countOfSuboperations, _countOfSuccessfulSuboperations;
    NSMutableDictionary *miscDictionary;
    NSMutableDictionary *logEntry;
    DcmDataset *originalDataset;
    
    NSMutableData *wadoRSData;
    unsigned long wadoRSSize, wadoRSReceivedSize;
    BOOL wadoRSConnectionActive;
    NSString *incomingPath, *wadoRSBoundary;
    NSThread *mainThread;
    NSTimeInterval childrenTimeInterval;
    DicomDatabase *db;
    
    NSString *localStudyName, *localSudyDescription;
}

@property( readonly) DcmDataset *originalDataset;
@property( readonly) NSMutableDictionary *miscDictionary;
@property( readonly) NSTimeInterval childrenTimeInterval;
@property BOOL dontCatchExceptions;
@property BOOL isAutoRetrieve;
@property BOOL noSmartMode;
@property NSUInteger countOfSuboperations, countOfSuccessfulSuboperations;
@property (retain) NSString *abstractSyntax, *incomingPath, *wadoRSBoundary, *localStudyName, *localSudyDescription;
@property (retain, nonatomic) DicomDatabase *db;
@property( retain) NSMutableDictionary *logEntry;

+ (NSURLSession*) dicomWebURLSession;

+ (void) errorMessage:(NSArray*) msg;
+ (void) errorURL:(NSDictionary*) msg;

+ (NSString*) boundaryFromHeaders: (NSDictionary*) headers;
+ (NSString*) syntaxStringForTransferSyntaxCode: (TransferSyntaxCodes) ts;

+ (id)queryNodeWithDataset:(DcmDataset *)dataset
			callingAET:(NSString *)myAET  
			calledAET:(NSString *)theirAET  
			hostname:(NSString *)hostname 
			port:(int)port 
			transferSyntax:(int)transferSyntax
			compression: (float)compression
			extraParameters:(NSDictionary *)extraParameters;
			
- (id)initWithDataset:(DcmDataset *)dataset
			callingAET:(NSString *)myAET  
			calledAET:(NSString *)theirAET  
			hostname:(NSString *)hostname 
			port:(int)port 
			transferSyntax:(int)transferSyntax
			compression: (float)compression
			extraParameters:(NSDictionary *)extraParameters;

- (void) setNumberOfImages: (NSNumber*) n;
- (void) setModality:(NSString*) m;
- (NSString *)comment;
- (NSString *)comments;
- (NSNumber*)rawNoFiles;
- (NSString*)type;
- (NSString *)uid;
- (NSString*) studyInstanceUID;
- (NSString*) seriesInstanceUID;
- (BOOL) isDistant;
- (NSString *)theDescription;
- (NSString *)name;
- (NSString *)rawName;
- (DCMCalendarDate *)birthdate;
- (NSString *)patientID;
- (NSString *)accessionNumber;
- (NSString *)bodyPartExamined;
- (NSString *)manufacturerModelName;
- (NSString *)referringPhysician;
- (NSString *)patientSex;
- (NSString *)performingPhysician;
- (NSString *)institutionName;
- (NSDate *)firstImageDate;
- (NSDate *)lastImageDate;
- (NSTimeInterval) acquisitionDuration;
- (DCMCalendarDate *)date;
- (DCMCalendarDate *)time;
- (NSString *)modality;
- (NSNumber *)numberImages;
- (NSArray *)children;
- (void) setChildren: (NSArray *) c;
- (void)purgeChildren;
- (void)addChild:(DcmDataset *)dataset;
- (DcmDataset *)queryPrototype;
- (DcmDataset *)queryPrototypeIMAGELevel;
- (DcmDataset *)moveDataset;
- (BOOL) isWorkList;
- (BOOL) deleteObjectOnServer;
// values are a NSDictionary the key for the value is @"value" key for the name is @"name"  name is the tag descriptor from the tag dictionary
- (BOOL) queryAllChildren;
- (BOOL) queryWithValues:(NSArray *)values;
- (BOOL) queryWithValues:(NSArray *)values dataset:(DcmDataset*) dataset;
- (BOOL) queryWithValues:(NSArray *)values dataset:(DcmDataset*) dataset syntaxAbstract:(NSString*) syntaxAbstract;
- (void)setShowErrorMessage:(BOOL) m;
//common network code for move and query
- (BOOL)setupNetworkWithSyntax:(const char *)abstractSyntax dataset:(DcmDataset *)dataset;
- (BOOL)setupNetworkWithSyntax:(const char *)abstractSyntax dataset:(DcmDataset *)dataset destination:(NSString*) destination;
- (OFCondition) addPresentationContext:(T_ASC_Parameters *)params abstractSyntax:(const char *)abstractSyntax;

- (OFCondition)findSCU:(T_ASC_Association *)assoc dataset:( DcmDataset *)dataset;
- (OFCondition) cfind:(T_ASC_Association *)assoc dataset:(DcmDataset *)dataset;

- (OFCondition) cmove:(T_ASC_Association *)assoc network:(T_ASC_Network *)net dataset:(DcmDataset *)dataset;
- (OFCondition) cmove:(T_ASC_Association *)assoc network:(T_ASC_Network *)net dataset:(DcmDataset *)dataset destination: (char*) destination;
- (OFCondition) moveSCU:(T_ASC_Association *)assoc  network:(T_ASC_Network *)net dataset:( DcmDataset *)dataset;
- (OFCondition) moveSCU:(T_ASC_Association *)assoc  network:(T_ASC_Network *)net dataset:( DcmDataset *)dataset destination: (char*) destination;

- (OFCondition) cget:(T_ASC_Association *)assoc network:(T_ASC_Network *)net dataset:(DcmDataset *)dataset;
- (OFCondition) getSCU:(T_ASC_Association *)assoc  network:(T_ASC_Network *)net dataset:( DcmDataset *)dataset;

- (void) move:(NSDictionary*) dict retrieveMode: (int) retrieveMode;
- (void) move:(NSDictionary*) dict;

- (NSMutableURLRequest*) URLRequest;

//- (void) sendMessage: (NSString*) abstractSyntax command: (int) cmd;

+ (dispatch_semaphore_t)semaphoreForServerHostAndPort:(NSString*)key;
+ (BOOL) addAuthenticationToRequest: (NSMutableURLRequest*) request fromParameters: (NSMutableDictionary*) d;
@end
#endif
