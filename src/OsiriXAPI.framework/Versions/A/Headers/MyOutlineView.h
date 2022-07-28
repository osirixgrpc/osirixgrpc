/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/


#import <Cocoa/Cocoa.h>
#import "OSIOutlineView.h"

/** \brief OutlineView for BrowserController */
@interface MyOutlineView : OSIOutlineView
{
}

- (void)hideAllColumns;
- (BOOL)isColumnWithIdentifierVisible:(id)identifier;
- (void)setColumnWithIdentifier:(id)identifier visible:(BOOL)visible;
- (void)setColumnWithIdentifier:(id)identifier visible:(BOOL)visible position: (int) position;
- (void)restoreColumnState:(NSObject *)columnState;
- (NSObject<NSCoding>*)columnState;

@end
