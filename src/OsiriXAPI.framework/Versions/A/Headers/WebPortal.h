/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "HTTPServer.h"

@class WebPortalDatabase, WebPortalSession, WebPortalServer, DicomDatabase;

@interface WebPortal : NSObject {
@private
	WebPortalDatabase* database;
	DicomDatabase* dicomDatabase;
	NSMutableArray* sessions;
	NSLock* sessionsArrayLock;
	NSLock* sessionCreateLock;
	BOOL usesSSL;
	NSInteger portNumber;
	NSString* address;
	BOOL authenticationRequired;
	BOOL passwordRestoreAllowed;
	BOOL wadoEnabled;
	BOOL weasisEnabled;
	BOOL flashEnabled;
    BOOL ohifEnabled;
    NSInteger poolSize;
    NSMutableDictionary *createPasswordDictionary;
	
	BOOL notificationsEnabled;
	NSInteger notificationsInterval;
	NSTimer* notificationsTimer, *temporaryUsersTimer;
	
	NSMutableDictionary* cache;
	NSMutableDictionary* locks;
	NSMutableArray *runLoops, *runLoopsLoad, *httpThreads;
	WebPortalServer *server;
	NSThread *serverThread;
}

// called from AppController
+(void)initializeWebPortalClass;
+(void)finalizeWebPortalClass;

+(WebPortal*)defaultWebPortal;
+(BOOL) isWebPortalInitialized;
+(WebPortal*)wadoOnlyWebPortal;
+(WebPortal*)auditWebPortal;

+(NSDictionary*)webServicesHTMLFiles;

@property(readonly, retain) WebPortalDatabase* database;
@property(readonly, retain) DicomDatabase* dicomDatabase;
@property(readonly, retain) NSMutableDictionary* cache, *createPasswordDictionary;
@property(readonly, retain) NSMutableDictionary* locks;
@property(readonly, retain) NSMutableArray* sessions;

@property(readonly) NSMutableArray *runLoops, *runLoopsLoad, *httpThreads;

@property (nonatomic) BOOL usesSSL;
@property (nonatomic) NSInteger portNumber, poolSize;
@property(retain) NSString* address;

@property BOOL authenticationRequired;
@property BOOL passwordRestoreAllowed;

@property BOOL wadoEnabled;
@property BOOL weasisEnabled;
@property (nonatomic) BOOL ohifEnabled;
@property BOOL flashEnabled;

@property (nonatomic) BOOL notificationsEnabled;
@property (nonatomic) NSInteger notificationsInterval;

-(id)initWithDatabase:(WebPortalDatabase*)database dicomDatabase:(DicomDatabase*)dd;
-(id)initWithDatabaseAtPath:(NSString*)sqlFilePath dicomDatabase:(DicomDatabase*)dd;

- (NSThread*) threadForRunLoopRef: (CFRunLoopRef) runloopref;

-(NSData*)dataForPath:(NSString*)rel;
+(NSData*)dataForPath:(NSString*)file;
+(NSString*)pathForPath:(NSString*)path;
+(NSArray*)filesForDirectory:(NSString*)path;
+(NSArray*)filesForDirectory:(NSString*)dirPath forExtension: (NSString*) extension;
+(NSString*)pathForPath:(NSString*)file includeInMemoryFiles: (BOOL) includeInMemoryFiles;
-(NSString*)stringForPath:(NSString*)file;

-(WebPortalSession*)newSession;
-(WebPortalSession*)addSession:(NSString*) sid;
-(void)deleteSessionId:(NSString*)sid;
-(WebPortalSession*)sessionForId:(NSString*)sid;
-(WebPortalSession*)sessionForUsername:(NSString*)username token:(NSString*)token;
-(void)clearSessions;
-(id)sessionForUsername:(NSString*)username token:(NSString*)token doConsume: (BOOL) doConsume;

-(NSString*)URL;
//-(NSString*)URLForAddress:(NSString*)address;

@end


@interface WebPortalServer : HTTPServer {
	WebPortal* portal;
}

@property(readonly, assign) WebPortal* portal;

@end
