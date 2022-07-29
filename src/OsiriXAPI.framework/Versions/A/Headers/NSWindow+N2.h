/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface NSWindow (N2)

-(NSSize)contentSizeForFrameSize:(NSSize)frameSize;
-(NSSize)frameSizeForContentSize:(NSSize)contentSize;

-(CGFloat)toolbarHeight;

-(void)safelySetMovable:(BOOL)flag;
//-(void)safelySetUsesLightBottomGradient:(BOOL)flag;

@end
