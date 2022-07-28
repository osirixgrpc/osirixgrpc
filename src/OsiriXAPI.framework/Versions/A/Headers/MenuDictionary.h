/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
//#import "NSMenu.h"


/** \brief MenuDictionary category used to modify contextual menus */
@interface NSMenu (MenuDictionary)
- (NSMenu*)initWithTitle:(NSString *)aTitle withDictionary:(NSDictionary *)aDictionary forWindowController:(NSWindowController *)aWindowController;

@end
