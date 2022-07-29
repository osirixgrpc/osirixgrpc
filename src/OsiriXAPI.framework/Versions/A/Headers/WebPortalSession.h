/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

extern NSString* const SessionIPAddressKey; // NSString
extern NSString* const SessionUsernameKey; // NSString
extern NSString* const SessionCookieName; // NSString
extern NSString* const SessionLastActivityDateKey; // NSDate
extern NSString* const SessionUserIDKey; // objectID.URIRepresentation.absoluteString
extern NSString* const SessionDontDisplayUser;  // NSNumber

@interface WebPortalSession : NSObject <NSCoding> {
@private
	NSMutableDictionary* dict;
	NSString* sid;
	NSLock* dictLock;
    
    BOOL requireDoubleAuthentication, doubleAuthenticated;
    NSString *doubleAuthenticationToken;
    NSString *usernameForDoubleAuthentication, *phoneForDoubleAthentication;
    NSTimeInterval timeStampForDoubleAuthentication;
    
    NSTimeInterval sessionCreationDateTimeInterval;
}

@property(retain) NSString* sid;
@property(retain) NSMutableDictionary* dict;
@property BOOL requireDoubleAuthentication, doubleAuthenticated;
@property(retain) NSString *doubleAuthenticationToken, *usernameForDoubleAuthentication, *phoneForDoubleAthentication;
@property NSTimeInterval timeStampForDoubleAuthentication, sessionCreationDateTimeInterval;

-(id)initWithId:(NSString*)isid;

-(void)setObject:(id)o forKey:(NSString*)k;
-(id)objectForKey:(NSString*)k;

-(NSString*)createToken;
-(NSString*)createTokenForUser: (NSString*) username;

-(BOOL)consumeToken:(NSString*)token;
-(BOOL)consumeToken:(NSString*)token user: (NSString**) user;

-(BOOL)containsToken:(NSString*)token;
-(BOOL)containsToken:(NSString*)token user:(NSString**) user;

-(NSString*)newChallenge;
-(NSString*)challenge;
-(void)deleteChallenge;

@end

