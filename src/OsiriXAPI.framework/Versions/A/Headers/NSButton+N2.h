/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSButton (N2)

-(id)initWithOrigin:(NSPoint)origin title:(NSString*)title font:(NSFont*)font;

-(NSSize)optimalSizeForWidth:(CGFloat)width;
-(NSSize)optimalSize;

@end
