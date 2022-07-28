/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSMutableDictionary (N2)

-(void)removeObject:(id)obj;
-(void) setObjectIfNonNil: (id) obj forKey: (NSString*) key;
-(void)setBool:(BOOL)b forKey:(NSString*)key;
-(void) changeKeyFrom:(NSString*) oldkey to:(NSString*) newKey;
@end
