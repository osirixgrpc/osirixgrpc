/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2MutableUInteger : NSObject {
	NSUInteger _value;
}

+(id)mutableUIntegerWithUInteger:(NSUInteger)value;

@property NSUInteger unsignedIntegerValue;

-(id)initWithUInteger:(NSUInteger)value;

-(void)increment;
-(void)decrement;

@end
