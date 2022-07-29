/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <Cocoa/Cocoa.h>

@interface O2DicomPredicateEditorPopUpButton : NSPopUpButton {
    NSMenu* _contextualMenu;
	NSString* _noSelectionLabel;
    NSWindow* _menuWindow;
}

@property(retain) NSMenu* contextualMenu;
@property(retain,nonatomic) NSString* noSelectionLabel;

@end
