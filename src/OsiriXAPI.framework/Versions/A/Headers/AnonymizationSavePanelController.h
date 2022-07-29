/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "AnonymizationPanelController.h"

enum AnonymizationSavePanelEnds {
	AnonymizationSavePanelSaveAs = AnonymizationPanelOk,
	AnonymizationSavePanelAdd,
	AnonymizationSavePanelReplace
};

@class AnonymizationViewController;

@interface AnonymizationSavePanelController : AnonymizationPanelController {
	NSString* outputDir; // valid if Save As...
}

@property(retain) NSString* outputDir;

-(IBAction)actionOk:(NSView*)sender;
-(IBAction)actionAdd:(NSView*)sender;
-(IBAction)actionReplace:(NSView*)sender;

@end
