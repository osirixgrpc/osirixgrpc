/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "HTTPConnection.h"
#import "WebPortalUser.h"

@class WebPortal, WebPortalDatabase, WebPortalServer, WebPortalSession, WebPortalResponse, DicomDatabase;

@interface WebPortalConnection : HTTPConnection
{
    BOOL dealloc;
    
	NSLock *sendLock, *running;
	WebPortalUser* user;
	WebPortalSession* session;
	
	NSString* requestedPath;
	NSString* GETParams;
    NSURL* requestedURL;
	NSDictionary* parameters; // GET and POST params
	
	WebPortalResponse* response;
	
    DicomDatabase* _independentDicomDatabase;
    NSThread* _independentDicomDatabaseThread;
    
    WebPortalDatabase* _independentDatabase;
    NSThread* _independentDatabaseThread;
    
    // POST / PUT support
    NSMutableData *STOWRSData;
    NSMutableArray *STOWRSDicomFiles;
    NSMutableDictionary *STOWRSLogEntry;
	NSArray *partsFromPOSTData;
    
#ifndef NDEBUG
    NSThread *initThread;
#endif
}

-(CFHTTPMessageRef)request;

@property(retain,readonly) WebPortalResponse* response;
@property(retain, nonatomic) WebPortalSession* session;
@property(retain) WebPortalUser* user;
@property(retain) NSDictionary* parameters;
@property(retain) NSString* GETParams;
@property(retain) NSURL* requestedURL;
@property(readonly) DicomDatabase* independentDicomDatabase;
@property(readonly) WebPortalDatabase* independentDatabase;

@property(assign,readonly) WebPortalServer* server;
@property(assign,readonly) WebPortal* portal;
@property(assign,readonly) AsyncSocket* asyncSocket;

@property(readonly) NSArray *partsFromPOSTData;

+(NSString*)FormatParams:(NSDictionary*)dict;
+(NSDictionary*)ExtractParams:(NSString*)paramsString;
+(NSString*) cleanUsername: (NSString*) username;
+(void) setLogHTTPRequest: (BOOL) v;

-(BOOL)requestIsIPhone;
-(BOOL)requestIsMobile;
-(BOOL)requestIsIPad;
-(BOOL)requestIsIPod;
-(BOOL)requestIsIOS;
-(BOOL)requestIsMacOS;
-(NSString*)contentType;
-(NSString*)acceptHeader;
-(NSString*)requestMethod;
-(NSDictionary*)headerFields;
-(NSString*)portalURL;
-(NSString*)portalURLScheme;
-(NSString*)publicURL;
-(NSString*)dicomCStorePortString;
- (void) resetPOST;
- (void) fillSessionAndUserVariables;
- (NSString*) clientIPAddress;
- (BOOL) isLocalClient;
@end

