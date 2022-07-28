/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2ImageButtonCell : NSButtonCell {
	NSImage* altImage;
}

@property(retain) NSImage* altImage;

-(id)initWithImage:(NSImage*)image altImage:(NSImage*)altImage;

@end
