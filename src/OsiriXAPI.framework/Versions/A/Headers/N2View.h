/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

@class N2Layout;

extern NSString* N2ViewBoundsSizeDidChangeNotification;
extern NSString* N2ViewBoundsSizeDidChangeNotificationOldBoundsSize;

@interface N2View : NSView {
	NSControlSize _controlSize;
	NSSize _minSize, _maxSize;
	N2Layout* _n2layout;
	NSColor* _foreColor;
	NSColor* _backColor;
}

@property NSControlSize controlSize;
@property NSSize minSize, maxSize;
@property(readonly) N2Layout *layout; // backward compatibility (example: EjectionFraction plugin)
@property(retain) N2Layout* n2layout;
@property(nonatomic, retain) NSColor* foreColor;
@property(nonatomic, retain) NSColor* backColor;

-(void)formatSubview:(NSView*)view;
-(void)resizeSubviews;

@end

