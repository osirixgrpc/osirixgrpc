//
//  ShadingArrayController.h
//  OsiriX
//
/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>
#import "OSIWindowController.h"

@interface ShadingArrayController : NSArrayController {
	BOOL				_enableEditing;
	OSIWindowController	*winController;
}

- (BOOL)enableEditing;
- (void)setEnableEditing:(BOOL)enable;
- (void)setWindowController:(OSIWindowController*) ctrl;

@end
