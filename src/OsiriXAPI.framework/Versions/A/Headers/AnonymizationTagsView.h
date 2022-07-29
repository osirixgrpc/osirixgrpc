/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>


@class DCMAttributeTag, AnonymizationViewController, AnonymizationTagsPopUpButton, N2TextField;

@interface AnonymizationTagsView : NSView {
	NSMutableArray* viewGroups;
	NSSize intercellSpacing, cellSize;
	IBOutlet AnonymizationViewController* anonymizationViewController;
	AnonymizationTagsPopUpButton* dcmTagsPopUpButton;
	NSButton* dcmTagAddButton;
}

-(void)addTag:(DCMAttributeTag*)tag;
-(void)removeTag:(DCMAttributeTag*)tag;
-(NSSize)idealSize;

-(NSButton*)checkBoxForObject:(id)object;
-(N2TextField*)textFieldForObject:(id)object;

-(void)addButtonAction:(NSButton*)sender;
@end
