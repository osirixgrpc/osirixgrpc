/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "BrowserController.h"

@class DataNodeIdentifier, DicomDatabase;

@interface BrowserController (Sources)

-(void)awakeSources;
-(void)deallocSources;

-(void)redrawSources;
- (void) menuWillOpenSources:(NSMenu *)menu;
-(DataNodeIdentifier*)sourceIdentifierAtRow:(int)row;
-(int)rowForDatabase:(DicomDatabase*)database;
-(DataNodeIdentifier*)sourceIdentifierForDatabase:(DicomDatabase*)database;
-(void)selectCurrentDatabaseSource;

-(int)findDBPath:(NSString*)path dbFolder:(NSString*)DBFolderLocation __deprecated;
-(void)removePathFromSources:(NSString*) path;
-(NSArray*) localDatabases;
-(void)setStatus:(int) status forRemoteDatabase:(NSDictionary*) dict;
@end
