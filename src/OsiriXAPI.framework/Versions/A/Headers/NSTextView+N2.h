/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSTextView (N2)

+(NSTextView*)labelWithText:(NSString*)string;
+(NSTextView*)labelWithText:(NSString*)string alignment:(NSTextAlignment)alignment;

-(NSSize)adaptToContent;
-(NSSize)adaptToContent:(CGFloat)maxWidth;

-(NSSize)optimalSizeForWidth:(CGFloat)width;
-(NSSize)optimalSize;

@end
