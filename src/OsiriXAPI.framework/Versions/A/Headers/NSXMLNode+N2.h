/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>


@interface NSXMLNode (N2)

+(id)elementWithName:(NSString*)name text:(NSString*)text;
+(id)elementWithName:(NSString*)name unsignedInt:(NSUInteger)value;
+(id)elementWithName:(NSString*)name bool:(BOOL)value;
-(NSXMLNode*)childNamed:(NSString*)childName;

@end
