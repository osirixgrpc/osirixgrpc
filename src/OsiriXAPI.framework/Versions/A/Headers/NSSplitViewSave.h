/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/




#import <Foundation/Foundation.h>
#import <AppKit/NSSplitView.h>

/** \brief Category saves splitView state to User Defaults */
@interface NSSplitView(Defaults)

- (void) restoreDefault: (NSString *) defaultName;
- (void) saveDefault: (NSString *) defaultName;
- (CGFloat)positionOfDividerAtIndex:(NSInteger)dividerIndex;

@end
