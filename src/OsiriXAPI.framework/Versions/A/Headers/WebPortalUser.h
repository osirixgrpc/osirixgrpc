/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

#define HASHPASSWORD @"**********"

/** \brief  Core Data Entity for a web user */
@class WebPortalStudy, DicomDatabase;

@interface WebPortalUser : NSManagedObject {
}

@property (nonatomic, retain) NSString * address;
@property (nonatomic, retain) NSNumber * autoDelete;
@property (nonatomic, retain) NSNumber * canAccessPatientsOtherStudies;
@property (nonatomic, retain) NSNumber * canSeeAlbums;
@property (nonatomic, retain) NSNumber * canDeleteStudy;
@property (nonatomic, retain) NSDate * creationDate;
@property (nonatomic, retain) NSDate * lastConnectionDate;
@property (nonatomic, retain) NSDate * deletionDate;
@property (nonatomic, retain) NSNumber * downloadZIP;
@property (nonatomic, retain) NSString * email;
@property (nonatomic, retain) NSNumber * emailNotification;
@property (nonatomic, retain) NSNumber * encryptedZIP;
@property (nonatomic, retain) NSNumber * isAdmin;
@property (nonatomic, retain) NSString * name;
@property (nonatomic, retain) NSString * password;
@property (nonatomic, retain) NSString * passwordHash;
@property (nonatomic, retain) NSDate * passwordCreationDate;
@property (nonatomic, retain) NSString * phone;
@property (nonatomic, retain) NSNumber * sendDICOMtoAnyNodes;
@property (nonatomic, retain) NSNumber * sendDICOMtoSelfIP;
@property (nonatomic, retain) NSNumber * shareStudyWithUser;
@property (nonatomic, retain) NSNumber * createTemporaryUser;
@property (nonatomic, retain) NSString * studyPredicate;
@property (nonatomic, retain) NSNumber * uploadDICOM;
@property (nonatomic, retain) NSNumber * downloadReport;
@property (nonatomic, retain) NSNumber * editReport;
@property (nonatomic, retain) NSNumber * uploadDICOMAddToSpecificStudies;
@property (nonatomic, retain) NSSet* studies;
@property (nonatomic, retain) NSSet* recentStudies;
@property (nonatomic, retain) NSNumber * showRecentPatients;
@property (nonatomic, retain) NSString * iprestriction;
@property (nonatomic, retain) NSNumber * cannotChangePassword;
@property (nonatomic, retain) NSNumber * onePatientOnly;
@property (nonatomic, retain) NSNumber * uploadDocumentToStudy;
@property (nonatomic, retain) NSNumber * studyOldestDate;
@property (nonatomic, retain) NSNumber * studyOldestDateLimitation;
@property (nonatomic, retain) NSNumber * dontUseStudyPredicateForPACSOnDemand;
@property (nonatomic, retain) NSNumber * requireDoubleAuthentication;
@property (nonatomic, retain) NSString * comment;
@property (nonatomic, retain) NSNumber * patientTemporaryAccount;
@property (nonatomic, retain) NSNumber * dontAcceptExternalIPAddress;

+ (BOOL) dontValidatePredicate;
+ (void) setDontValidatePredicate: (BOOL) b;

-(void)generatePassword;
-(void)convertPasswordToHashIfNeeded;

-(BOOL)validatePassword:(NSString**)value error:(NSError**)error;
-(BOOL)validateDownloadZIP:(NSNumber**)value error:(NSError**)error;
-(BOOL)validateName:(NSString**)value error:(NSError**)error;
-(BOOL)validateStudyPredicate:(NSString**)value error:(NSError**)error;
-(BOOL)isAuthorizedToAccessTo:(id) object;
-(NSArray*)arrayByAddingSpecificStudiesToArray:(NSArray*)array;

-(NSArray*)studiesForPredicate:(NSPredicate*)predicate;
-(NSArray*)studiesForPredicate:(NSPredicate*)predicate sortBy:(NSString*)sortValue;
-(NSArray*)studiesForPredicate:(NSPredicate*)predicate sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies;

+(NSArray*)studiesForUser: (WebPortalUser*) user predicate:(id)predicate;
+(NSArray*)studiesForUser: (WebPortalUser*) user predicate:(id)predicate sortBy:(NSString*)sortValue;
+(NSArray*)studiesForUser: (WebPortalUser*) user predicate:(id)predicate sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies;
+(NSArray*)studiesForUser: (WebPortalUser*) user predicate:(id)predicate sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies dicomDatabase: (DicomDatabase*) dicomDatabase;
+(NSArray*)studiesForUser: (WebPortalUser*) user predicate:(id)predicate sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies dicomDatabase: (DicomDatabase*) dicomDatabase localStudiesOnly: (BOOL) localStudiesOnly;
+(NSArray*)studiesForUser: (WebPortalUser*) user album:(NSString*)albumName sortBy:(NSString*)sortValue sortOrder:(NSComparisonResult) sortOrder fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies;
+(NSArray*)studiesForUser: (WebPortalUser*) user album:(NSString*)albumName sortBy:(NSString*)sortValue sortOrder:(NSComparisonResult) sortOrder fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies dicomDatabase: (DicomDatabase*) dicomDatabase;

-(NSArray*)studiesForAlbum:(NSString*)albumName;
-(NSArray*)studiesForAlbum:(NSString*)albumName sortBy:(NSString*)sortValue;
-(NSArray*)studiesForAlbum:(NSString*)albumName sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies;

+(NSArray*)studiesForUser: (WebPortalUser*) user album:(NSString*)albumName;
+(NSArray*)studiesForUser: (WebPortalUser*) user album:(NSString*)albumName sortBy:(NSString*)sortValue;
+(NSArray*)studiesForUser: (WebPortalUser*) user album:(NSString*)albumName sortBy:(NSString*)sortValue fetchLimit:(int) fetchLimit fetchOffset:(int) fetchOffset numberOfStudies:(int*) numberOfStudies;
+(BOOL)evaluePredicateForDICOMQuery:(NSPredicate*) p0 inDictionary:(NSMutableDictionary*) dict;
+ (void) purgeStudiesForUserCache;
@end

@interface WebPortalUser (CoreDataGeneratedAccessors)

- (void)addStudiesObject:(WebPortalStudy*)value;
- (void)removeStudiesObject:(WebPortalStudy*)value;
- (void)addStudies:(NSSet *)value;
- (void)removeStudies:(NSSet *)value;
- (void)addRecentStudies:(NSSet *)value;
- (void)removeRecentStudies:(NSSet *)value;
- (void) applyDefaultSettings;
@end

