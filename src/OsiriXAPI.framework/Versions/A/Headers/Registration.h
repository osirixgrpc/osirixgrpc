/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#if !TARGET_OS_IOS
#import <Cocoa/Cocoa.h>
#endif

#define REGPHPURL @"reg/reg.php"
//#define REGPHPOVHURL @"reg/min/index.php"
#define WSPHPURL @"ws/ws.php"

@interface Registration : NSObject
+ (NSString*) obfuscatedKey;
+ (NSString*) stringFromEncodedArray:(NSArray*) array;
+ (NSString*) stringFromEncodedArray:(NSArray*) array validServerResponse: (BOOL*) validServerResponse;
+ (NSString*) stringFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (NSString*) stringFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters validServerResponse: (BOOL*) validServerResponse;
+ (NSString*) encodedStringWithParameters:(NSDictionary*) parameters urlEncoded: (BOOL) urlEncoded;
+ (NSURL*) encodedURLWithPath:(NSString*) pathURL withParameters:(NSDictionary*) parameters baseURL:(NSURL*) baseURL;
+ (NSArray*) arrayFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (NSData*) dataFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (NSArray*) POSTJSON:(id) json encodedToURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (NSArray*) POSTData:(NSData*) dataToPost encodedToURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (NSString*) stringFromPOSTJSON: (id) json encodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;

+ (id) dictionaryOrArrayFromPOSTJSON: (id) json encodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;

+ (NSString*) stringFromPOSTData: (NSData*) dataToPOST encodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;

+ (id) dictionaryOrArrayFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters;
+ (id) dictionaryOrArrayFromEncodedURL:(NSString*) pathURL withParameters:(NSDictionary*) parameters validServerResponse: (BOOL*) validServerResponse;

+ (NSData*) encodeData:(NSData*) dataIn;
+ (NSData*) decodeData:(NSData*) dataIn;

+ (NSDictionary*) loadRegistrationDictionary;
+ (NSDictionary*) loadRegistrationDictionaryReload:(BOOL) reload;

+ (void) saveRegistrationDictionary: (NSDictionary*) dict;
+ (BOOL) isRegAlive;
+ (BOOL) isRegAliveOK;
+ (NSString*) machineModel;
+ (NSString *) machineCPU;
+ (NSString*) OSXVersion;
+ (NSArray*) IPv4Address;
+ (NSString*) IPv4AddressAsString;
+ (NSHost*) currentHost;
+ (void) DNSResolve:(id) o;
+ (NSArray*) currentHostNames;
+ (NSArray*) currentHostAddresses;
+ (NSString*) MACAddress;
+ (NSURL*) baseURL;
+ (NSURL*) baseOVHURL;
+ (BOOL) validateEmail: (NSString *) candidate;

#ifndef NDEBUG
+ (void) setInfomaniakDown: (BOOL) v;
+ (void) setInfomaniakDownValidatedFromOVH: (BOOL) v;
#endif
@end
