/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2Shell : NSObject

+(NSString*)execute:(NSString*)path;
+(NSString*)execute:(NSString*)path arguments:(NSArray*)arguments;
+(NSString*)execute:(NSString*)path arguments:(NSArray*)arguments outStatus:(int*)outStatus;
+(NSString*)execute:(NSString*)path arguments:(NSArray*)arguments expectedStatus:(int)expectedStatus;
+(NSString*)hostname;
+(NSString*)ip;
+(NSString*)mac;
+(NSString*)serialNumber;
+(int)userId __deprecated; // getuid()

@end
