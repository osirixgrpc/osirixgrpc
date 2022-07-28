/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2TextField : NSTextField {
//	NSColor* invalidContentBackgroundColor;
	BOOL formatIsOk;
}

//@property(retain) NSColor* invalidContentBackgroundColor;
@property(nonatomic, readonly) BOOL formatIsOk;

@end
