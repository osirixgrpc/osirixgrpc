/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "HTTPResponse.h"

@class WebPortalConnection, WebPortalSession, WebPortal;

@interface WebPortalResponse : HTTPDataResponse {
	WebPortalConnection* wpc;
	WebPortal* portal;
	NSMutableDictionary* httpHeaders;
	NSString* templateString;
	NSMutableDictionary* tokens;
	int statusCode;
}

@property(assign,readonly) WebPortalConnection* wpc;
@property(retain) NSData* data;
@property(readonly) NSMutableDictionary* httpHeaders;
@property(retain) NSString* mimeType;
@property(retain) NSString* templateString;
@property(readonly) NSMutableDictionary* tokens;
@property(assign) int statusCode;

-(id)initWithWebPortalConnection:(WebPortalConnection*)wpc;
//-(id)initWithData:(NSData*)data mime:(NSString*)mime sessionId:(NSString*)sessionId __deprecated;
-(void)setSessionId:(NSString*)sessionId;
-(void)setDataWithString:(NSString*)str;

//+(NSRange)string:(NSString*)string rangeOfFirstOccurrenceOfBlock:(NSString*)b;
//+(void)mutableString:(NSMutableString*)string block:(NSString*)blockTag setVisible:(BOOL)visible;
+(void)mutableString:(NSMutableString*)string evaluateTokensWithDictionary:(NSDictionary*)localtokens context:(id)context;

@end


@interface WebPortalProxy : NSObject {
	NSObject* object;
	NSArray* transformers;
}

@property(readonly, retain) NSObject* object;
@property(readonly, retain) NSArray* transformers;

+(id)createWithObject:(NSObject*)o transformer:(id)t;
-(id)valueForKey:(NSString*)k context:(id)context;

@end


@interface WebPortalProxyObjectTransformer : NSObject

+(id)create;
-(id)valueForKey:(NSString*)k object:(NSObject*)o context:(id)context;

@end


@interface NSMutableDictionary (WebPortalProxy)

-(void)addError:(NSString*)error;
-(void)addMessage:(NSString*)message;
-(NSMutableArray*)errors;

@end


@interface InfoTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end


@interface StringTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end


/*@interface ArrayTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end


@interface SetTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end*/


@interface DateTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end


@interface DicomStudyTransformer : WebPortalProxyObjectTransformer
+(id)create;
//+ (void) clearOtherStudiesForThisPatientCache;
@end


@interface DicomSeriesTransformer : WebPortalProxyObjectTransformer {
	NSSize size;
}
+(id)create;
@end


@interface WebPortalUserTransformer : WebPortalProxyObjectTransformer
+(id)create;
@end
