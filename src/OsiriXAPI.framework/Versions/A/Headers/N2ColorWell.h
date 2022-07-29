/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "N2Button.h"


@interface N2ColorWell : N2Button {
	NSColor* _color;
}

@property(nonatomic, retain) NSColor* color;

@end
