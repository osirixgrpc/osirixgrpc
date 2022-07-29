/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSView (N2)

// Shortcut to [NSView initWithFrame:NSMakeRect(NSZeroPoint, size)]
-(id)initWithSize:(NSSize)size;
-(NSRect)sizeAdjust;
-(NSImage *) screenshotByCreatingPDF;

@end

@protocol OptimalSize

-(NSSize)optimalSize;
-(NSSize)optimalSizeForWidth:(CGFloat)width;

@end
