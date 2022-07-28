/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import <PreferencePanes/NSPreferencePane.h>


@interface NSPreferencePane (OsiriX)

-(BOOL)isUnlocked;
-(NSNumber*)editable;

@end
