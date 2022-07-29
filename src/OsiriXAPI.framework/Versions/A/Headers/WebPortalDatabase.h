/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "N2ManagedDatabase.h"


@class WebPortalUser;


@interface WebPortalDatabase : N2ManagedDatabase {
}

extern NSString* const WebPortalDatabaseUserEntityName;
extern NSString* const WebPortalDatabaseStudyEntityName;
extern NSString* const WebPortalDatabaseRecentStudyEntityName;

-(NSEntityDescription*)userEntity;
-(NSEntityDescription*)studyEntity;
-(NSEntityDescription*)recentStudyEntity;

-(NSArray*)usersWithPredicate:(NSPredicate*)p;

-(WebPortalUser*)userWithName:(NSString*)name;
-(WebPortalUser*)newUser;

@end
