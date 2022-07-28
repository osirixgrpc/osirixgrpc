/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <AppKit/AppKit.h>

@interface ComparativeCell : NSButtonCell
{
    NSString *_rightTextFirstLine, *_rightTextSecondLine, *_leftTextSecondLine, *_leftTextFirstLine;
    NSColor *_textColor;
}

@property(retain) NSString *rightTextFirstLine, *rightTextSecondLine, *leftTextSecondLine, *leftTextFirstLine;
@property(retain) NSColor *textColor;

@end
