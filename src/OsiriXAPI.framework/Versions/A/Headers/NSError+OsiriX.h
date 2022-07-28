/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSError (OsiriX)

extern NSString* const OsirixErrorDomain;

+(NSError*)osirixErrorWithCode:(NSInteger)code localizedDescription:(NSString*)desc;
+(NSError*)osirixErrorWithCode:(NSInteger)code localizedDescriptionFormat:(NSString*)format, ...;
+(NSError*)osirixErrorWithCode:(NSInteger)code underlyingError:(NSError*)underlyingError localizedDescription:(NSString*)desc;
+(NSError*)osirixErrorWithCode:(NSInteger)code underlyingError:(NSError*)underlyingError localizedDescriptionFormat:(NSString*)format, ...;

@end
