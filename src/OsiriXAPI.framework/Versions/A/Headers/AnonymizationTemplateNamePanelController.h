/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>


@interface AnonymizationTemplateNamePanelController : NSWindowController {
	IBOutlet NSTextField* nameField;
	IBOutlet NSButton* okButton;
	IBOutlet NSButton* cancelButton;
	NSArray* replaceValues;
}

@property(readonly) NSTextField* nameField;
@property(readonly) NSButton* okButton;
@property(readonly) NSButton* cancelButton;
@property(retain) NSArray* replaceValues;

-(id)initWithReplaceValues:(NSArray*)values;

-(NSString*)value;

-(IBAction)okButtonAction:(id)sender;
-(IBAction)cancelButtonAction:(id)sender;

@end
