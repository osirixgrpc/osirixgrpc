/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@class DCMAttributeTag;

@interface AnonymizationCustomTagPanelController : NSWindowController {
	IBOutlet NSTextField* groupField;
	IBOutlet NSTextField* elementField;
}

-(IBAction)cancelButtonAction:(id)sender;
-(IBAction)okButtonAction:(id)sender;

@property(assign) DCMAttributeTag* attributeTag;

@end
