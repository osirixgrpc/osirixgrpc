/*=========================================================================
 Program:   OsiriX
 Copyright (c) 2010 - 2020 Pixmeo SARL
 266 rue de Bernex
 CH-1233 Bernex
 Switzerland
 All rights reserved.
 =========================================================================*/

#import "AppController.h"

@interface AppController (TouchBar) <NSTouchBarDelegate>

+ (NSTouchBar*)defaultTouchBar;
+ (BOOL) isTouchBarAvailable;
+ (NSTouchBarItem*)buttonTouchBarItemWithIdentifier:(NSTouchBarItemIdentifier)identifier title:(NSString*)title customizationLabel:(NSString*)customizationLabel image:(NSImage*)image target:(id)target action:(SEL)action;
+ (NSTouchBarItem*)buttonTouchBarItemWithIdentifier:(NSTouchBarItemIdentifier)identifier type:(NSButtonType)type title:(NSString*)title customizationLabel:(NSString*)customizationLabel image:(NSImage*)image target:(id)target action:(SEL)action;

@end
