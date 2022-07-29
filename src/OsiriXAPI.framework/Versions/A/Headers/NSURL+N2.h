/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2URLParts : NSObject {
	NSString *_protocol, *_address, *_port, *_path, *_params;
}

@property(retain) NSString *protocol, *address, *port, *path, *params;
@property(readonly) NSString* pathAndParams;

@end


@interface NSURL (N2)

-(N2URLParts*)parts;
+(NSURL*)URLWithParts:(N2URLParts*)parts;

- (NSURL *)URLByAppendingQueryParameters:(NSDictionary *)queryParameters;
- (NSURL *)URLByRemovingQueryParameters:(NSArray *)queryKeys;
- (NSDictionary*)queryItems;

@end
