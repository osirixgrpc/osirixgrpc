/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>

extern NSString* N2DisclosureBoxDidToggleNotification;
extern NSString* N2DisclosureBoxWillExpandNotification;
extern NSString* N2DisclosureBoxDidExpandNotification;
extern NSString* N2DisclosureBoxWillCollapseNotification;
extern NSString* N2DisclosureBoxDidCollapseNotification;

@interface N2DisclosureBox : NSBox {
	BOOL _showingExpanded;
	IBOutlet NSView* _content;
	CGFloat _contentHeight;
}

@property BOOL enabled;

-(id)initWithTitle:(NSString*)title content:(NSView*)view;
-(void)toggle:(id)sender;
-(void)expand:(id)sender;
-(void)collapse:(id)sender;
-(BOOL)isExpanded;

@end
