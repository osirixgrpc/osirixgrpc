/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface N2Pair : NSObject {
	id _first, _second;
}

@property(retain) id first, second;

-(id)initWith:(id)first and:(id)second;

@end
