/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "WebPortal.h"


@class WebPortalUser;
@class DicomFile;

@interface WebPortal (EmailLog)

+(BOOL)isExternalIPAddress:(NSString*) string;

-(void)emailNotifications;
-(BOOL)sendNotificationsEmailsTo:(NSArray*)users aboutStudies:(NSArray*)filteredStudies predicate:(NSString*)predicate customText:(NSString*)customText;
-(BOOL)sendNotificationsEmailsTo:(NSArray*)users aboutStudies:(NSArray*)filteredStudies predicate:(NSString*)predicate customText:(NSString*)customText from:(WebPortalUser*) from;

-(void)updateLogEntryForStudy:(NSManagedObject*)study withMessage:(NSString*)message forUser:(NSString*)user ip:(NSString*)ip;
-(void)updateLogEntryForDictionary:(NSDictionary*)study withMessage:(NSString*)message forUser:(NSString*)user ip:(NSString*)ip;
-(void)updateLogEntryForDicomFile:(DicomFile*)study withMessage:(NSString*)message forUser:(NSString*)user ip:(NSString*)ip;

-(WebPortalUser*)newUserWithEmail:(NSString*)email;

@end
