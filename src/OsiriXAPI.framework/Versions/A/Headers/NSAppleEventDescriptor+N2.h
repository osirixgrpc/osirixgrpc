/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>


@interface NSObject (Scripting)

-(NSAppleEventDescriptor*)appleEventDescriptor;

@end


@interface NSAppleEventDescriptor (Scripting)

-(id)object;
+(NSDictionary*)dictionaryWithArray:(NSArray*)array;

@end
