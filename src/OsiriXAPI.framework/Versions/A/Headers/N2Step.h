/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

extern NSString* N2StepDidBecomeActiveNotification;
extern NSString* N2StepDidBecomeInactiveNotification;
extern NSString* N2StepDidBecomeEnabledNotification;
extern NSString* N2StepDidBecomeDisabledNotification;
extern NSString* N2StepTitleDidChangeNotification;

@interface N2Step : NSObject {
	NSString* _title;
	NSView* _enclosedView;
	NSButton* defaultButton;
	BOOL _necessary, _active, _enabled, _done, _shouldStayVisibleWhenInactive;
}

@property(nonatomic, retain) NSString* title;
@property(readonly) NSView* enclosedView;
@property(retain) NSButton* defaultButton;
@property(getter=isNecessary) BOOL necessary;
@property(nonatomic, getter=isActive) BOOL active;
@property(nonatomic, getter=isEnabled) BOOL enabled;
@property(getter=isDone) BOOL done;
@property BOOL shouldStayVisibleWhenInactive;

-(id)initWithTitle:(NSString*)title enclosedView:(NSView*)view;

@end
