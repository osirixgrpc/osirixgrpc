/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface NSInvocation (N2)

+(NSInvocation*)invocationWithSelector:(SEL)sel target:(id)target;
+(NSInvocation*)invocationWithSelector:(SEL)sel target:(id)target argument:(id)arg;
-(void)setArgumentObject:(id)o atIndex:(NSUInteger)i;
-(id)returnValue;

@end
