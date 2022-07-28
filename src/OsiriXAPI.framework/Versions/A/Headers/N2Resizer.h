/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@interface N2Resizer : NSObject {
	NSView* _observed;
	NSView* _affected;
	BOOL _resizing;
}

@property(retain) NSView* observed;
@property(retain) NSView* affected;

-(id)initByObservingView:(NSView*)observed affecting:(NSView*)affected;

@end
