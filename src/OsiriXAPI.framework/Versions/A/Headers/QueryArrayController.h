/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class DCMTKRootQueryNode;
@class DicomDatabase;

/** \brief Controller for performing query */
@interface QueryArrayController : NSObject
{
	DCMTKRootQueryNode *rootNode;
	NSMutableDictionary *filters;
	NSString *callingAET;
	NSString *calledAET;
	NSString *hostname;
	NSString *port;
	NSArray *queries;
	NSDictionary *distantServer;
	NSLock *queryLock;
	int retrieveMode;
    DicomDatabase *db;
}

@property (retain, nonatomic) DicomDatabase *db;

- (id)initWithCallingAET:(NSString *) myAET distantServer: (NSDictionary*) ds;

- (id)rootNode;
- (NSArray *)queries;
- (NSMutableDictionary*) filters;
- (void)addFilter:(id)filter forDescription:(NSString *)description;
- (void)sortArray:(NSArray *)sortDesc;
- (BOOL)performQuery;
- (NSDictionary *)parameters;
- (BOOL)performQuery: (BOOL) showError;

@end
