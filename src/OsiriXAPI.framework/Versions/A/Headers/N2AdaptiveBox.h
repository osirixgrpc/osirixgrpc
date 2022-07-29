/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2AdaptiveBox : NSBox {
	NSSize idealContentSize;
}

-(void)setContentView:(NSView*)view;
-(NSAnimation*)adaptContainersToIdealSize:(NSSize)size;
-(NSAnimation*)adaptContainersToIdealSize;

@end


@interface NSWindowController (N2AdaptiveBox)

-(NSAnimation*)synchronizeSizeWithContent;

@end
